#include "ladder.h" 
#include <algorithm>


void error(string word1, string word2, string msg)
{
    cerr << "Error with words '" << word1 << "' and '" << word2 << "': " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    if(abs(int(str1.length()) - int(str2.length())) > d)
    {
        return false;
    }

    return is_adjacent(str1, str2);
}

bool is_adjacent(const string& word1, const string& word2)
{
    if(abs(int(word1.length()) - int(word2.length())) > 1)
    {
        return false;
    }

    if(word1.length() == word2.length())
    {
        int diff = 0;
        for(size_t i = 0; i < word1.length(); ++i)
        {
            if(word1[i] != word2[i])
            {
                diff++;
                if(diff > 1)
                {
                    return false;
                }
            }
        }
        return diff == 1;
    }

    const string& shorter = (word1.length() < word2.length()) ? word1 : word2;
    const string& longer = (word1.length() < word2.length()) ? word2 : word1;

    for(size_t i = 0; i <= shorter.length(); ++i)
    {
        bool match = true;

        for(size_t j = 0; j < i; ++j)
        {
            if(shorter[j] != longer[j])
            {
                match = false;
                break;
            }
        }

        if(match)
        {
            for(size_t j = i; j < shorter.length(); ++j)
            {
                if(shorter[j] != longer[j + 1])
                {
                    match = false;
                    break;
                }
            }
        }
        
        if(match)
        {
            return true;
        }

        return false;


    }
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word)
    {
        return {begin_word};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});


    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for(const string& word : word_list)
        {
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end())
            {
                visited.insert(word);

                vector<string> new_ladder = ladder;

                new_ladder.push_back(word);

                if(word == end_word)
                {
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
            }
        }
    }


    return {};

}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream file(file_name);
   
    string word;
    while(file >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.empty())
    {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder (" << ladder.size() << " steps):" << endl;
    for(size_t i = 0; i < ladder.size(); ++i)
    {
        cout << ladder[i];
        if(i < ladder.size() - 1)
        {
            cout << "-> ";
        }
    }
    cout << endl;
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
