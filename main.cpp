#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

#include <unistd.h>

using namespace std;

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

void drawScrollS(vector<string>& lines, int maxLen)
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
vector<string> dataIntoVector(istream& in, int maxLen)
{
    vector<string> res;
    string word = "";
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

// main [options] [<file>]
// main [options] [<text>]
int main(int argc, char** argv)
{
    // Flags and values
    int maxLen = 32;
    bool meFlag = false;
    bool sigFlag = false;
    string sig = "";

    // Get options
    int opt;
    while ((opt = getopt(argc, argv, ":w:s:i")) != -1)
    {
        switch (opt)
        {
            case 'w':
                maxLen = stoi(optarg);
                break;
            case 'i':
                meFlag = true;
                break;
            case 's':
                sigFlag = true;
                sig = optarg;
                break;
        }
    }

    istream* in;
    ifstream file;
    string filename;
    vector<string> data;

    if (optind < argc)
    {
        // Something passed in as non-opt at end
        filename = argv[optind];
        file.open(filename.c_str());
        if (!file)
        {
            // Treat as plain text
            istringstream str(filename);
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
        cout << "Done reading" << endl;
    }
    data = dataIntoVector(*in, maxLen);
    drawScrollS(data, maxLen);

    return 0;
}

