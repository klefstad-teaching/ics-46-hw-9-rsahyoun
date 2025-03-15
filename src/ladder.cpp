#include "ladder.h" 
#include <algorithm>


void error(string word1, string word2, string msg)
{
    cerr << "Error with words '" << word1 << "' and '" << word2 << "': " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    if(str1 == str2)
    {
        return true;
    }

    if(abs(int(str1.length()) - int(str2.length())) > d)
    {
        return false;
    }

    if(d == 1)
    {
        return is_adjacent(str1, str2);
    }

    const size_t len1 = str1.length();
    const size_t len2 = str2.length();
    
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
    
    for(size_t i = 0; i <= len1; i++)
        dp[i][0] = i;
    
    for(size_t j = 0; j <= len2; j++)
        dp[0][j] = j;
    
    for(size_t i = 1; i <= len1; i++) 
    {
        for(size_t j = 1; j <= len2; j++) 
        {
            if(str1[i-1] == str2[j-1])
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }
    
    return dp[len1][len2] <= d;
}

bool is_adjacent(const string& word1, const string& word2)
{

    if(word1 == word2)
    {
        return true;
    }

    int len1 = word1.length();
    int len2 = word2.length();

    if(abs(int(len1) - int(len2)) > 1)
    {
        return false;
    }

    if(len1 == len2)
    {
        int diff = 0;
        for(size_t i = 0; i < len1; ++i)
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
    int char1count = 0;
    int char2count = 0;

    bool skipped = false;
    while(char1count < len1 && char2count < len2)
    {
        if(word1[char1count] != word2[char2count])
        {
            if(skipped)
            {
                return false;
            }

            skipped = true;

            if(len1 > len2)
            {
                char1count++;
            }
            else
            {
                char2count++;
            }

        }
        else
        {
            char1count++;
            char2count++;
        }
    }

    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word)
    {
        return {};
    }

    if (begin_word != end_word && word_list.find(begin_word) == word_list.end() || word_list.find(end_word) == word_list.end()) 
    {
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);


    while(!ladder_queue.empty())
    {
        int level_sz = ladder_queue.size();
        set<string> curr_level_visited;

        for(int i = 0; i < level_sz; ++i)
        {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();

            for(const string& word : word_list)
            {
                if(is_adjacent(last_word, word) && visited.find(word) == visited.end())
                {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if(word == end_word)
                    {
                        return new_ladder;
                    }

                    ladder_queue.push(new_ladder);
                    curr_level_visited.insert(word);
                }
            }

        }

        
        visited.insert(curr_level_visited.begin(), curr_level_visited.end());
    }


    return {};

}

void load_words(set<string>& word_list, const string& file_name)
{
    ifstream file(file_name);

    if (!file) 
    {
        throw runtime_error("Could not open dictionary file");
    }
   
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

    cout << "Word ladder found: ";
    for(size_t i = 0; i < ladder.size(); ++i)
    {
        cout << ladder[i];
        if(i < ladder.size() - 1)
        {
            cout << " ";
        }
    }
    cout << " " <<endl;
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
