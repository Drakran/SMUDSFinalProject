#include "parser.h"


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
    std::string filePath = "./scotus"; // ./Files
    std::string delimeter = "/";
    std::string fileNum = "\0";
    std::string allFilesInFolder = "\0";
    for(unsigned i = 0; i < 100; i++){
        std::cout << "\nNEXT FILE: \n";
        fileNum = fileNames[i];
        allFilesInFolder = filePath + delimeter + fileNum;
        std::ifstream firstFile(allFilesInFolder);
        if(!firstFile){
            std::cerr << "File could not be read." << std::endl;
            exit(EXIT_FAILURE);
        }
        //Gets the Json file and Parses it
        std::string jstring( (std::istreambuf_iterator<char>(firstFile) ),(std::istreambuf_iterator<char>() ) );
        const char* json = jstring.c_str(); //String to cstring
        rapidjson::Document cases;
        cases.Parse(json);

        string plain = cases["plain_text"].GetString();
        //std::cout << "PLain Text" << plain;
        std::cout << cases["resource_uri"].GetString() << '\n';

        //
        //
        if(!cases["html"].IsNull())
        {
             string htmlString = cases["html"].GetString();
             std::cout << htmlString;
             HtmlParser htmlParser(htmlString);
             htmlParser.parse();
        }




        //static const char* html = cases["html"].GetString();
        //std::cout << htmlString;
//        if(!)
//        {

//        }


        //Polish dude;


//        static const char* xml = "element";
//       tinyxml2::XMLDocument doc;
//       doc.Parse(html);
//       std::cout << doc.Error();
//       doc.Print();
      // std::cout << doc.ErrorID();


        // basic init
            //myhtml_t* myhtml = myhtml_create();
//            myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

//            // first tree init
//            myhtml_tree_t* tree = myhtml_tree_create();
//            myhtml_tree_init(tree, myhtml);

//            // parse html
//            myhtml_parse(tree, MyENCODING_UTF_8, html, std::strlen(html));

//            // print result
//            // or see serialization function with callback: myhtml_serialization_tree_callback
//            mycore_string_raw_t str = {0};
//            myhtml_serialization_tree_buffer(myhtml_tree_get_document(tree), &str);
//            printf("%s\n", str.data);

//            // release resources
//            mycore_string_raw_destroy(&str, false);
//            myhtml_tree_destroy(tree);
//            myhtml_destroy(myhtml);

        //std::cout << jstring;
        firstFile.close();
    }
}


