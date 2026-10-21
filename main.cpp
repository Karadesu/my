#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char* argv[]) {
    bool show_lines = 0;
    bool show_bytes = 0;
    bool show_words = 0;
    bool show_alnum = 0;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            continue;
        }

        if (argv[i][1] == '-') {
            if (strcmp(argv[i],"--lines") == 0) {
                show_lines = 1;
            } else if (strcmp(argv[i],"--bytes") == 0) {
                show_bytes = 1;
            } else if (strcmp(argv[i],"--words") == 0) {
                show_words = 1;
            } else if (strcmp(argv[i],"--alnum") == 0) {
                show_alnum = 1;
            }
        } else {
            if (strcmp(argv[i], "-l")==0) {
                show_lines = 1;
            }   

            if (strcmp(argv[i], "-c")==0) {
                show_bytes = 1;
            }

            if (strcmp(argv[i], "-w")==0) {
                show_words = 1;
            }

            if (strcmp(argv[i], "-a")==0) {
                show_alnum = 1;
            }
        }
            if (argv[i][1] != '-') {
                for (int j = 1; argv[i][j] != '\0'; ++j) {
                    if (argv[i][j] == 'l') {
                        show_lines = 1;
                    } else if (argv[i][j] == 'c') {
                        show_bytes = 1;
                    } else if (argv[i][j] == 'w') {
                        show_words = 1;
                    } else if (argv[i][j] == 'a') {
                        show_alnum = 1;
                    }
                }
            }
        }

    if ((show_lines == 0) and (show_bytes == 0) and (show_words == 0) and (show_alnum == 0)) {
        show_lines = 1;
        show_words = 1;
        show_bytes = 1;
    }

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            continue;
        }

            char* filename = argv[i];
            char ch;
            char last_ch;
            int lines = 0; //Вывод только количества строк
            std::size_t bytes = 0; //Вывод размера файла в байтах
            int words = 0; //Вывод количества слов
            int alnum = 0; //Вывод количества латинских букв и цифр
            bool inword = false; 
            
            std::ifstream f(filename, std::ios::binary);
            if (!f) {
                std::cout << "file does not exist\n";
                continue;
            }

            while (f.get(ch)) {
                bytes += 1;
                
                if (ch == '\n') {
                    lines += 1;
                }

                if (!((ch != ' ') + (ch != '\n') + (ch != '\t') + (ch != '\r') + (ch != '\v') + (ch != '\f') == 6)) {
                    inword = false;
                } else {
                    if ((ch != ' ') + (ch != '\n') + (ch != '\t') + (ch != '\r') + (ch != '\v') + (ch != '\f') == 6) {
                        if (!inword) {
                            words += 1;
                            inword = true;
                        }
                    }
                }
                    
                if ((ch >= 'a' && ch <= 'z') + (ch >= 'A' && ch <= 'Z') + (ch >= '0' && ch <= '9') == 1) {
                    alnum += 1;
                }
                last_ch = ch;
            }

            if (bytes > 0 and last_ch != '\n') {
                lines += 1;
            }

            if (show_lines) {
                std::cout << lines << ' ';
            }

            if (show_words) {
                std::cout << words << ' ';
            }

            if (show_alnum) {
                std::cout << alnum << ' ';
            }    

            if (show_bytes) {
                std::cout << bytes << ' ';
            }

            std::cout << filename << '\n'; 
    }
    return 0;
}