#ifndef HIGHEST_SCORE_H_INCLUDED
#define HIGHEST_SCORE_H_INCLUDED
#include "option.h"
#include "highest_score.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct HighestScores {
    map<pair<int, int>, int> scores;

    void read_file(const string &filename) {
        ifstream file(filename);
        if (file.is_open()) {
            int mp, difficulty, score;
            while (file >> mp >> difficulty >> score) {
                scores[make_pair(mp, difficulty)] = score;
            }
            file.close();
        }
    }

    void write_file(const string &filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto &entry : scores) {
                file << entry.first.first << " "
                     << entry.first.second << " "
                     << entry.second << endl;
            }
            file.close();
        }
    }

    void update(int mp, int difficulty, int score) {
        auto key = make_pair(mp, difficulty);
        if (score > scores[key]) {
            scores[key] = score;
            write_file("highest_score.txt");
        }
    }
};

HighestScores Highest_Scores;

void render_score_text(Graphics graphics, const int mp, const int x) {
    Highest_Scores.read_file("highest_score.txt");

    TTF_Font* font = graphics.loadFont("SnakeFont.ttf", 60);
    SDL_Color color = {255, 255, 255};

    const int Text_width = 130;
    const int Text_height = 50;
    const int y = 540;

    int easy_score =  Highest_Scores.scores[make_pair(mp, EASY)];
    int medium_score =  Highest_Scores.scores[make_pair(mp, MEDIUM)];
    int hard_score =  Highest_Scores.scores[make_pair(mp, HARD)];

    stringstream easy_text, medium_text, hard_text;
    easy_text << "Easy: " << easy_score;
    medium_text << "Medium: " << medium_score;
    hard_text << "Hard: " << hard_score;

    SDL_Texture *Op1 = graphics.renderText(easy_text.str().c_str(), font, color);
    graphics.renderTexture(Op1, x, y, Text_width, Text_height);

    SDL_Texture *Op2 = graphics.renderText(medium_text.str().c_str(), font, color);
    graphics.renderTexture(Op2, x , y + Text_height, Text_width, Text_height);

    SDL_Texture *Op3 = graphics.renderText(hard_text.str().c_str(), font,  color);
    graphics.renderTexture(Op3, x, y + 2 * Text_height, Text_width, Text_height);
}

#endif // HIGHEST_SCORE_H_INCLUDED
