#include "snakegame.h"
using namespace std;
int Compare(PLAYER a, PLAYER b) {
    if (a.SCORE == b.SCORE) {
        if (a.TIME < b.TIME) return 1;
        else return 0;
    }
    else if (a.SCORE > b.SCORE) return 1;
    else return 0;
}
void SortLeaderBoard(PLAYER Player[], int size) {
    int maxidx;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (!Compare(Player[i],Player[j])) {//j > i 
                swap(Player[i], Player[j]);
            }
        }
    }
}
int LeaderBoard(PLAYER Player[]) {
    ifstream ifs;
    char s[100];
    ifs.open("highscore.txt");
    int arr_pos = 0;
    while (ifs.getline(s, 100)) {
        char* ptr = strtok(s, ",");
        //cout << ptr << " ";
        Player[arr_pos].name = ptr;
        ptr = strtok(NULL, ",");
        //cout << ptr << " ";
        string tmp = ptr;
        Player[arr_pos].TIME = stoll(tmp);
        ptr = strtok(NULL, ",");
        //cout << ptr << " ";
        tmp = ptr;
        Player[arr_pos].SCORE = stoi(tmp);
        //cout << "\n";
        ++arr_pos;
		/*cout << s << " ";
		//pos++;
		if (pos == 3) {
			pos = 0;
			i++; GoToXY(18, 24+i);*/
	}
    SortLeaderBoard(Player, arr_pos);
	return arr_pos;//size of the array
}