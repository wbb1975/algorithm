#include <fstream>

#include "SymbolFilter.h"
#include "FeedClient.h"
#include "Feed.h"
#include "MsgLog.h"

using namespace std;

CSymbolFilter::CSymbolFilter(): 
{
    m_pRoot = new TrieNode(0);
}


CSymbolFilter::~CSymbolFilter(void)
{
    for (TrieNodeList::iterator it = m_RecycleList.begin(); it != m_RecycleList.end(); ++it)
    {
        delete *it;
    }
    m_RecycleList.clear();

    delete m_pRoot;
}



bool CSymbolFilter::loadFilterFile(const char *pFilterFileName)
{
    return loadFilterFile(pFilterFileName, true, "");
}


bool CSymbolFilter::loadFilterFile(const char *pFilterFileName, bool checkVersionNum, const string &oldVersionNum)
{
    ifstream myfilterfile(pFilterFileName);
    if (!myfilterfile)
    {
        return false;
    }

    string::size_type first_pos, last_pos;
    string   line;
    int      iLineNum = 0;
    SymbolFilterState state = In_General;
    while (getline(myfilterfile, line))
    {
        iLineNum++;
        if (line.empty())
        {
            continue;
        }
        if (iLineNum == 1)     // like //File Version Number="3.79"
        {
            first_pos = line.find_first_of("\"");
            last_pos  = line.find_first_of("\"", first_pos + 1);
            if (first_pos == string::npos || last_pos == first_pos)
            {
                return false;
            }
            else
            {
                m_Version = line.substr(first_pos + 1, last_pos - first_pos - 1);
                if (m_Version == oldVersionNum)
                {
                    if (checkVersionNum)
                    {
                        return false;
                    }
                }
            }
            continue;
        }
        else if (iLineNum == 2)    // like //Deployment Type="TSfCP (DTC)"
        {
            first_pos = line.find_first_of("\"");
            last_pos  = line.find_first_of("\"", first_pos + 1);
            if (first_pos == string::npos || last_pos == first_pos)
            {
                return false;
            }
            else
            {
                m_DeploymentType = line.substr(first_pos + 1, last_pos - first_pos - 1);
            }
            continue;
        }

        if (_strnicmp(line.c_str(), PREFIX_SECTION_STR, PREFIX_SECTION_LEN) == 0)
        {
            state = In_Prefix;
            continue;
        }
        else if (_strnicmp(line.c_str(), SUFFIX_SECTION_STR, SUFFIX_SECTION_LEN) == 0)
        {
            state = In_Suffix;
            continue;
        }
        else if (_strnicmp(line.c_str(), FULLNAME_SECTION_STR, FULLNAME_SECTION_LEN) == 0)
        {
            state = In_Fullname;
            continue;
        }
        else if (_strnicmp(line.c_str(), FILTER_COMMENT_STR, FILTER_COMMENT_LEN) == 0)
        {
            continue;
        }
        else
        {
            switch (state)
            {
                case In_General:
                    break;
                case In_Prefix:
                    if (line.length() > MAX_PREFIX_LEN)
                    {
                        break;
                    }
                    insertPrefix(line);
                    break;
                case In_Suffix:
                    if (line.length() > MAX_SUFFIX_LEN)
                    {
                        break;
                    }
                    insertSuffix(line);
                    break;
                case In_Fullname:
                    insertFullname(line);
                    break;
            }
        }
    }

    return true;
}


bool CSymbolFilter::insertPrefix(const std::string &line)
{
    bool result = true;

    TrieNode *currNode = m_pRoot;
    int       currChar = 0;
    for (size_t idx = 0; idx < line.length(); ++idx)
    {
        currChar = line[idx];
        if (currChar >= MAX_SYMBOL_CHARACTERS)
        {
            return false;
        }
        if (currNode->nextLevelSlots[currChar] != 0)
        {
            currNode = currNode->nextLevelSlots[currChar];
            continue;
        }
        else
        {
            TrieNode *pNode = new TrieNode(currChar);
            currNode->nextLevelSlots[currChar] = pNode;
            currNode->subCount++;

            m_RecycleList.insert(pNode);      // help destructor

            currNode = pNode;
        }
    }

    currNode->hasEnd = true;
    m_PrefixList.push_back(line);               // help Dump

    return result;
}

bool CSymbolFilter::insertSuffix(const std::string &line)
{
    m_SuffixList.push_back(line);
    return true;
}


bool CSymbolFilter::insertFullname(const std::string &line)
{
    m_FullnameFilteres.insert(line);
    m_FullnameList.push_back(line);

    return true;
}


bool CSymbolFilter::ricFilterOut(const std::string &line)
{
    bool result = false;

    // Prefix check
    TrieNode *currNode = m_pRoot;
    int       currChar = 0;
    for (size_t idx = 0; idx < line.length(); ++idx)
    {
        currChar = line[idx];
        if (currChar >= MAX_SYMBOL_CHARACTERS)
        {
            break;
        }
        if (currNode->nextLevelSlots[currChar] != 0)
        {
            currNode = currNode->nextLevelSlots[currChar];
            if (currNode->value == currChar && currNode->hasEnd)
            {
                return true;
            }
        }
        else
        {
            break;         // no slot. we will filter in
        }
    }

    // suffix check

    // Fullname check
    FilterList::iterator it = m_FullnameFilteres.find(line);
    if (it != m_FullnameFilteres.end())
    {
        return true;
    }

    return result;
}


int CSymbolFilter::dumpFilterContent(const char *pFilterFileName)
{
    ofstream myfilterfile(pFilterFileName);
    if (!myfilterfile)
    {
        return FEED_FAIL;
    }

    myfilterfile << "//File Version Number=\"" << m_Version << "\"\n";
    myfilterfile << "//Deployment Type=\"" << m_DeploymentType << "\"\n";

    myfilterfile << PREFIX_SECTION_STR << endl;
    StrList::iterator it;
    for (it = m_PrefixList.begin(); it !=  m_PrefixList.end(); ++it)
    {
        myfilterfile << *it << endl;
    }

    myfilterfile << SUFFIX_SECTION_STR << endl;

    myfilterfile << FULLNAME_SECTION_STR << endl;
    for (it = m_FullnameList.begin(); it !=  m_FullnameList.end(); ++it)
    {
        myfilterfile << *it << endl;
    }

    return FEED_SUCCESS;
}


void CSymbolFilter::swap(CSymbolFilter &anotherFilter)
{
    // swap version
    string temp               = anotherFilter.m_Version;
    anotherFilter.m_Version   = m_Version;
    m_Version                 = temp;

    // swap deploymentType
    temp                           = anotherFilter.m_DeploymentType;
    anotherFilter.m_DeploymentType = m_DeploymentType;
    m_DeploymentType               = temp;

    // swap Prefix Search tree and recycle list
    TrieNode *pTemp         = anotherFilter.m_pRoot;
    anotherFilter.m_pRoot   = m_pRoot;
    m_pRoot                 = pTemp;
    m_RecycleList.swap(anotherFilter.m_RecycleList);
    m_PrefixList.swap(anotherFilter.m_PrefixList);

    // swap Suffix stuff
    m_SuffixList.swap(anotherFilter.m_SuffixList);
    // TODO

    // swap fullanme stuff
    m_FullnameFilteres.swap(anotherFilter.m_FullnameFilteres);
    m_FullnameList.swap(anotherFilter.m_FullnameList);
}
