#include "parser.h"

// time ./Program5 /home/student/Desktop/scotus

Parser::Parser()
{

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
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
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

void Parser::parse()
{
    std::map<std::string,int> wordCase;
    std::regex reg("<.*?>"); // <[^/]*>
    std::regex line("\n");
    std::string filePath = "./scotus"; // ./Files
    std::string delimeter = "/";
    std::string fileNum = "\0";
    std::string allFilesInFolder = "\0";
    for(unsigned i = 0; i < 1000; i++){
        //std::cout << "\nNEXT FILE: \n";
        fileNum = fileNames[i];
        allFilesInFolder = filePath + delimeter + fileNum;
        std::ifstream firstFile(allFilesInFolder);
        if(!firstFile){
            std::cerr << "File could not be read." << std::endl;
            exit(EXIT_FAILURE);
        }
        //Gets the Json file and Parses it
        std::string jstring( (std::istreambuf_iterator<char>(firstFile) ),(std::istreambuf_iterator<char>() ) );
        firstFile.close();
        const char* json = jstring.c_str(); //String to cstring
        rapidjson::Document cases;
        cases.Parse(json);

       // string plain = cases["plain_text"].GetString();

        //std::cout << htmlString;
        //std::cout << "PLain Text" << plain;
        //std::cout << cases["resource_uri"].GetString() << '\n';
        if(!cases["html"].IsNull())
        {
            std::istringstream ss{std::regex_replace(cases["html"].GetString(),reg, " ")};
            //std::string html = (std::regex_replace(cases["html"].GetString(),reg, " "));
            //std::istringstream ss{std::regex_replace(html,line, " ")};
            std::string temp;
            //temp = "Meow";

            //std::cout << ss.str();
            //words(std::istream_iterator<std::string>{ss},std::istream_iterator<std::string>{});
            while(ss >> temp)
            {
                temp.erase (std::remove_if (temp.begin (), temp.end (), ispunct), temp.end ());
                Porter2Stemmer::stem(temp);
                ++wordCase[temp];
                //ss.ignore();
            }
        }

    }
//    for(std::map<std::string,int>::iterator iter = wordCase.begin(); iter!=wordCase.end(); iter++)
//    {
//        std::cout << "Key: " << iter->first << " Value:" << iter->second <<  '\n';
//    }
//    std:: string test = "seems";
//    Porter2Stemmer::stem(test);


//    std::cout << "Skyler " << test << std::endl;
}



