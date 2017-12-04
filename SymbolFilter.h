#ifndef CSYMBOLFILTER_H_
#define CSYMBOLFILTER_H_

#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

#ifndef MAX_SYMBOL_CHARACTERS
#define MAX_SYMBOL_CHARACTERS  127
#endif


#ifndef SYMBOL_FILTER_MACROS
#define SYMBOL_FILTER_MACROS
#define MAX_PREFIX_LEN 25
#define MAX_SUFFIX_LEN 25

#define FILTER_COMMENT_STR   "//"
#define FILTER_COMMENT_LEN   2
#define PREFIX_SECTION_STR   "[Prefix]"
#define PREFIX_SECTION_LEN   8
#define SUFFIX_SECTION_STR   "[Suffix]"
#define SUFFIX_SECTION_LEN   8
#define FULLNAME_SECTION_STR "[Fullname]"
#define FULLNAME_SECTION_LEN 10
#endif

struct TrieNode
{
    TrieNode   *nextLevelSlots[MAX_SYMBOL_CHARACTERS];
    char        value;
    bool        hasEnd;
    int         subCount;

    TrieNode(char c)
    {
        memset(nextLevelSlots, 0x00, sizeof(nextLevelSlots));
        hasEnd   = false;
        value    = c;
        subCount = 0;
    }
};


class FeedClient;

class CSymbolFilter
{
public:
    typedef enum
    {
        In_General,
        In_Prefix,
        In_Suffix,
        In_Fullname,
    } SymbolFilterState;

    typedef std::unordered_set<TrieNode *>   TrieNodeList;
    typedef std::vector<std::string>         StrList;
    typedef std::unordered_set<std::string>  FilterList;

public:
    CSymbolFilter();
    CSymbolFilter(FeedClient *parent);
    ~CSymbolFilter(void);

    void setParent(FeedClient *parent);
    bool loadFilterFile(const char *pFileName);
    bool loadFilterFile(const char *pFileName, bool checkVersionNum, const std::string &oldVersionNum);
    bool ricFilterOut(const std::string &line);
    int  dumpFilterContent(const char  *pFileName);
    void swap(CSymbolFilter &anotherFilter);

    const std::string &getVersion() const
    {
        return m_Version;
    }
    const std::string &getDeploymentType() const
    {
        return m_DeploymentType;
    }

    size_t  totalTrieNodeCount() const
    {
        return m_RecycleList.size();
    }

    size_t  totalTrieNodeSize() const
    {
        return m_RecycleList.size() * sizeof(TrieNode);
    }

protected:
    bool insertPrefix(const std::string &line);
    bool insertSuffix(const std::string &line);
    bool insertFullname(const std::string &line);

    std::string             m_Version;
    std::string             m_DeploymentType;

    // The following members are used for RIC Prefix Filtering
    TrieNode                *m_pRoot;
    TrieNodeList             m_RecycleList;      // help destructor
    StrList                  m_PrefixList;       // help DumpRICPrefix

    // The following members are used for RIC Suffix Filtering
    // TODO
    StrList                  m_SuffixList;       // help DumpRICPrefix

    // The following members are for full name filtering
    FilterList               m_FullnameFilteres;
    StrList                  m_FullnameList;    // keep original order
};

#endif
