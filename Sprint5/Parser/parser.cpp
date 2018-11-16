#include "parser.h"

Parser::Parser()
{

}

void Parser::getFiles()
{
    /* adapted from:

     * https://stackoverflow.com/questions/612097

     * /how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c

     */

    std::vector<std::string> get_files_at_path_with_extn(std::string path, std::string extn) {

        vector<string> result;

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

            throw invalid_argument("Provided path could not be opened");

        }



        return result;

    }



    int main(int argc, char* argv[]) {

        string dir_path;

        string extention = ".json";



        if (argc < 2) {

            dir_path = ".";

        }

        else {

            dir_path = argv[1];

        }



        vector<string> files = get_files_at_path_with_extn(dir_path, extention);



        for (int i = 0; i < files.size(); i++)

            cout << files[i] << endl;



        return 0;

    }
}
