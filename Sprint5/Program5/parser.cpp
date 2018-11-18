#include "parser.h"

std::string strArray[155] = {"a", "about", "above", "after", "again", "against", "all", "am", "an",
                             "and", "any", "are", "as", "at", "be", "because", "been", "before", "being",
                             "below", "between", "both", "but", "by", "could", "did", "do", "does", "doing",
                             "down", "during", "each", "few", "for", "from", "further", "had", "has", "have",
                             "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers",
                             "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm",
                             "i've", "if", "in", "into", "is", "it", "it's", "its", "itself", "let's", "me",
                             "more", "most", "my", "myself", "no", "not", "nor", "of", "on", "once", "only", "or", "other",
                             "ought", "our", "ours", "ourselves", "out", "over", "own", "same", "she", "she'd",
                             "she'll", "she's", "should", "so", "some", "such", "than", "that", "that's", "the",
                             "their", "theirs", "them", "themselves", "then", "there", "there's", "these", "they",
                             "they'd", "they'll", "they're", "they've", "this", "those", "through", "to",
                             "too", "under", "until", "up", "very", "was", "we", "we'd", "we'll", "we're",
                             "we've", "were", "what", "what's", "when", "when's", "where", "where's", "which",
                             "while", "who", "who's", "whom", "why", "why's", "with", "would", "you", "you'd",
                             "you'll", "you're", "you've", "your", "yours", "yourself", "yourselves"};


Parser::Parser()
{
    OverallWordTotal = 0;
    for(int i = 0; i < 155; i++)//153 is number of stop words
        stopWords.insert(strArray[i]);
}

std::vector<std::string> Parser::getFiles(std::string path, std:: string extn)
{
    /* adapted from:
     * https://stackoverflow.com/questions/612097
     * /how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
     */
    std::vector<std::string> result;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            int len = strlen(ent->d_name);
            if (ent->d_type == DT_REG &&
                len > extn.length() &&
                strcmp(ent->d_name + len - extn.length(), extn.c_str()) == 0)
                result.push_back(ent->d_name);
        }
        closedir(dir);
    }
    else {
        throw std::invalid_argument("Provided path could not be opened");
    }
    fileNames = result;
    return result; //If want to send vector
}
bool Parser::isStopWord(std::string s)
{
    std::set<std::string>::iterator it;
    it = stopWords.find(s);
    if(it == stopWords.end())
        return false;
    return true;
}

/*The Parse function parses all the words for a set number of cases
 * using regex
 */

void Parser::parse(std::string filePath, std::string fileNum, IndexInterface<Word,std::string>& index)
{
    //This is the map of all the words and number of times it appear
    std::map<std::string,std::map<std::string,int>> wordtoCases;
    std::map<std::string,int> wordCase;
    std::regex reg("<.*?>"); // <[^/]*> //TH
    std::regex line("\n");
    std::string delimeter = "/";
    //fileNum = fileNames[i];
    std::ifstream firstFile(filePath);
    if(!firstFile){
        std::cerr << "File could not be read." << std::endl;
        exit(EXIT_FAILURE);
    }
    //Gets the Json file and Parses it
    std::string jstring( (std::istreambuf_iterator<char>(firstFile) ),(std::istreambuf_iterator<char>() ) );
    std::transform(jstring.begin(), jstring.end(), jstring.begin(), ::tolower);
    firstFile.close();
    const char* json = jstring.c_str(); //String to cstring
    rapidjson::Document cases;
    cases.Parse(json);

    //        if(strcmp(cases["plain_text"].GetString(), "") != 0)
    //        {

    //        }

    std::map<std::string, std::string> keepTrack;//Keep track of already stemmed words
    //Can be substitute by using a 'dictionary' text file
    if(!cases["html"].IsNull())
    {
        std::istringstream ss{std::regex_replace(cases["html"].GetString(),reg, " ")};
        std::string temp; //A single word
        while(ss >> temp)
        {
            temp.erase (std::remove_if (temp.begin (), temp.end (), ispunct), temp.end ());
            if(isStopWord(temp))
                temp = "";
            else
            {
                if(keepTrack.find(temp) != keepTrack.end())
                    ++wordCase[keepTrack.find(temp)->second];
                else
                {
                    std::string temp2 = temp;
                    Porter2Stemmer::stem(temp);
                    keepTrack.insert(std::pair<std::string, std::string>(temp2, temp));
                    ++wordCase[temp];

                }
            }
        }
    }
    //One Case is done (creating an indivual case)
    for(auto iter: wordCase )
    {
        Word caseWord;
        caseWord.setWord(iter.first);
        caseWord.upDateFileAndCount(fileNum, iter.second);
        //counting every single word parsed including repeteaded words.
        ++OverallWordTotal;
        try {
            //check if object exists and update that word object
            index.find(caseWord.getWord()).upDateFileAndCount( fileNum, iter.second);
        } catch (std::exception &e) {
            //object doesnt exitst so we insert in avl tree
            index.insert( caseWord, caseWord.getWord() );
        }
    }
/*
    //this is one to output each
    for(std::map<std::string,int>::iterator iter = wordCase.begin(); iter!=wordCase.end(); iter++)
    {
        std::cout << "Key: " << iter->first << " Value:" << iter->second <<  '\n';
    }
*/
}

int Parser :: getOverallWordTotal()
{
    return OverallWordTotal;
}




