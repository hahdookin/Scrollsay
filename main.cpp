#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>

#include <unistd.h>

using namespace std;

enum Align
{
    Left,
    Right,
    Center,
    Justify,
};

//" \U/_______          _____         ____/"
string topbar(int n)
{
    string start = " \\U/_";
    string end = "__/";
    string mid = "______          _____         __";
    return start + mid.substr(0, n - 1) + '_' + end;
}

// "   |____    _______    __  ____    ___|"
string botbar(int n)
{
    string start = "   |_";
    string end = "_|";
    string mid = "___    _______    __  ____    __";
    return start + mid.substr(0, n - 1) + '_' + end;
}

string repeat(char ch, int n)
{
    string res = "";
    for (int i = 0; i < n; i++) res += ch;
    return res;
}

string padding(int cur, int max)
{
    int spaces = max - cur;
    return repeat(' ', spaces);
}

void drawScrollS(list<string>& lines, int maxLen)
{
    string word;

    cout << " .-.-" << repeat('-', maxLen) << ".-." << endl;
    cout << "((o))" << repeat(' ', maxLen) << "   )" << endl;
    cout << topbar(maxLen) << endl;
    cout << "   | " << repeat(' ', maxLen) << " |" << endl;
    
    string start = "   | ";
    string end = " |";

    for (string& line : lines)
    {
        cout << start << line << end << endl;
    }
    
    cout << botbar(maxLen) << endl;
    cout << "  /A\\" << repeat(' ', maxLen) << "  \\" << endl;
    cout << " ((o))" << repeat(' ', maxLen-1) << "   )" << endl;
    cout << "  '-'" << repeat('-', maxLen) << "--'" << endl;
}
            
// Takes input from a stream and makes a vector
// of lines less than a max length of chars
list<string> dataIntoList(istream& in, int maxLen)
{
    list<string> res;
    string word;
    string str = "";
    while (in >> word)
    {
        if (str.size() + word.size() + 1 <= maxLen)
        {
            str += word + " ";
        }
        else
        {
            string pad = padding(str.size(), maxLen);
            res.push_back(str + pad);
            if (word.size() > maxLen)
            {
                while (word.size() > maxLen)
                {
                    res.push_back(word.substr(0, maxLen));
                    word = word.substr(maxLen);
                }
            }
            str = word;
            if (str.size() < maxLen) str += " ";
        }
    }
    res.push_back(str + padding(str.size(), maxLen));
    return res;
}

void applySignature(list<string>& data, string signature, int maxLen)
{
    string close_sal = "Sincerely,";
    string pad_before_sal;
    string pad_after_sal;
    if (signature.size() > close_sal.size())
    {
        pad_before_sal = padding(signature.size(), maxLen);
        pad_after_sal = padding(pad_before_sal.size() + close_sal.size(), maxLen);
    }
    else
    {
        pad_before_sal = padding(close_sal.size(), maxLen);
        pad_after_sal = "";
    }
    data.push_back(padding(0, maxLen));
    data.push_back(pad_before_sal + close_sal + pad_after_sal);
    data.push_back(padding(signature.size(), maxLen) + signature);
}

void applyI(list<string>& data, int maxLen)
{
    string formal_sal = "I hereby decree,";
    data.push_front(padding(0, maxLen));
    data.push_front(formal_sal + padding(formal_sal.size(), maxLen));
}

void usage()
{
    string tab = repeat(' ', 2);
    cout << "Usage: scrollsay [options] [FILE]" << endl;
    cout << endl;
    cout << "If FILE couldn't be opened, treats FILE as text literal." << endl;
    cout << "If FILE is not provided, tries to read from stdin." << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << tab << "-w <width>      Set max text width" << endl;
    cout << tab << "-i              You said it" << endl;
    cout << tab << "-s <signature>  Sign a name at the bottom" << endl;
    cout << tab << "-h              Print this message" << endl;
    cout << endl;
}

// main [options] [<file>]
// main [options] [<text>]
int main(int argc, char** argv)
{
    // Flags and values
    int maxLen = 32;
    bool iFlag = false;
    bool sFlag = false;
    string signature = "";
    bool aFlag = false;
    Align align = Left;

    /*if (argc == 1)
    {
        usage();
        return 0;
    }*/

    // Get options
    int opt;
    while ((opt = getopt(argc, argv, ":w:s:a:ih")) != -1)
    {
        switch (opt)
        {
            case 'w':
                try {
                    maxLen = stoi(optarg);
                } catch (invalid_argument e) {
                    cerr << "Invalid argument for -w: " << optarg << endl;
                    return 1;
                }
                break;

            case 'i':
                iFlag = true;
                break;

            case 's':
                sFlag = true;
                signature = optarg;
                break;

            case 'a':
                switch (optarg[0])
                {
                    case 'l':
                        align = Left;
                        break;
                    case 'r':
                        align = Right;
                        break;
                    case 'c':
                        align = Center;
                        break;
                    case 'j':
                        align = Justify;
                        break;
                }
                break;

            case 'h':
                usage();
                return 0;
        }
    }

    istream* in;
    istringstream str;
    ifstream file;
    string filename;
    list<string> data;

    if (optind < argc)
    {
        // Something passed in as non-opt at end
        filename = argv[optind];
        file.open(filename.c_str());
        if (!file)
        {
            // Treat as plain text
            str = istringstream(filename);
            in = &str;
        }
        else
        {
            // Treat as file text
            in = &file;
        }
    }
    else
    {
        // Something from stdin
        in = &cin;
    }

    data = dataIntoList(*in, maxLen);

    // apply some options: i, s
    if (iFlag) applyI(data, maxLen);
    if (sFlag) applySignature(data, signature, maxLen);

    drawScrollS(data, maxLen);

    return 0;
}

