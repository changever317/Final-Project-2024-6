#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<fstream>
#include<conio.h>
#include<sstream>
#include<windows.h>
using namespace std;
bool login(fstream &log , string &acc , int &bal , bool &is_login);
void tictactoe(int &bal);
void dancesimulator(int &bal);
void bingo(int &bal);
void menu(string &acc , int &bal , int &option);
void save(fstream &log ,string &acc , int &bal);

int main(){
    fstream log;
    string acc;
    int bal , option;
    bool is_login = false;
    log.open("Account.txt");
    if(!log.is_open()){
        cerr << "Cannot open the file." << endl;
        exit(1);
    }
    while(true){
        if(is_login){
            menu(acc,bal,option);
            if(option == 0)
                tictactoe(bal); 
            else if (option == 1){
                if(bal >= 100)
                    bingo(bal);
                else{
                    cout << "Your balance is not enough, please choose another game:" << endl;
                    continue;
                }                    
            }
            else if (option == 2)
                dancesimulator(bal);
            else if (option == 3){
                is_login = false;
                save(log,acc,bal);
                system("cls");
            }
            else if (option == 4){
                save(log,acc,bal);
                break;
            }
        }
        else
            is_login = login(log,acc,bal,is_login);
    }
    return 0;
}

bool login(fstream &log , string &acc , int &bal , bool &is_login){
    string pw,check;
    stringstream ss;
    log.clear();
    log.seekg(0,ios::beg);
    cout << "Enter your username: ";
    cin >> acc;
    char a;
    int count = 0;
    while(1){
        cout << "\rEnter your password: ";
        for(int i = 1 ; i <= count ; i++)
            cout << "*";
        a = getche();
        if(a == 8){
            count--;
            if(pw.size() > 0){
                pw.pop_back();
                cout << " ";
            }
        }
        else if (a == '\r')
            break;
        else{
            pw.push_back(a);
            count++;
        }
        if(count < 0)
            count = 0;
    }
    while(getline(log,check)){
        string checkac,checkpw;
        ss.str("");
        ss.clear();
        ss << check;
        ss >> checkac >> checkpw >> bal;
        //cout << endl <<  checkac << endl << checkpw  <<endl << bal;
        if(checkac == acc && checkpw == pw)
            return true;
    }
    if(!is_login){
            cout << endl << "Invalid account or password, press any key to retry.";
            char s;
            s = getche();
            system("cls");
            return login(log,acc,bal,is_login);
    }
    return true;
}

void tictactoe(int &bal){
    system("cls");
    srand(time(NULL));
    size_t count = 0;
    bool w1 = 0 , w2 = 0;
    int row , col ,  turn = 1;
    int map[3][3] = {0};
    while(w1 == 0 && w2 == 0){ //output the graph
        cout << "  0 1 2" << endl;
        for(int i = 0 ; i <= 2 ; i++){
            cout << i << " ";
            for(int j = 0 ; j <= 2 ; j++){
                if(map[i][j] == 0)
                    cout << "-"; 
                else if(map[i][j] == 1)
                    cout << "O";
                else if(map[i][j] == -1)
                    cout << "X";
                if(j != 2)
                    cout << " ";
            }
            cout << endl;
        } // output the graph
        if(turn == 1) {
            cout << "Your turn! Please enter the position to place your piece (row column): ";
            while(cin >> row >> col){
                if(row > 2 || row < 0 || col > 2 || col < 0)
                    cout << "Invalid input, please enter again:";
                else if (map[row][col] != 0)
                    cout << "The place is already taken, please enter again:";
                else{
                    map[row][col] += turn;
                    break;
                }
            }
        }
        else{
            cout << "Computer is thinking..." << endl;
            int comc , comr;
            while(true){
                comc = rand()%3;
                comr = rand()%3;
                if(map[comr][comc]==0){
                    map[comr][comc] = turn;
                    break;
                }
            }
        }
        count ++ ;
        //check winner
        for(int i = 0 ; i <= 2 ; i++){
            if(map[i][0] + map[i][1] + map[i][2] == 3 || map[0][i] + map[1][i] + map[2][i] == 3)
                w1 = 1;
            else if(map[i][0] + map[i][1] + map[i][2] == -3 || map[0][i] + map[1][i] + map[2][i] == -3)
                w2 = 1;
        }
        int wclu = 0 , wcru = 0; //win check from left upper slash and right upper slash
        for(int i = 0 ; i <= 2 ; i++){
            wclu += map[i][i];
            wcru += map[i][2-i];
        }
        if(wclu == 3 || wcru == 3)
            w1 = 1;
        else if (wclu == -3 || wcru == -3)
            w2 = 1;
        else if (w1 == 1 || w2 == 1)
            break;
        else if(count == 9)
            break;
        //check winner
        if(turn == 1)// check turn
            turn = -1;
        else if(turn == -1)
            turn = 1;
    } // check turn
        cout << "  0 1 2" << endl;
        for(int i = 0 ; i <= 2 ; i++){
            cout << i << " ";
            for(int j = 0 ; j <= 2 ; j++){
                if(map[i][j] == 0)
                    cout << "-"; 
                else if(map[i][j] == 1)
                    cout << "O";
                else if(map[i][j] == -1)
                    cout << "X";
                if(j != 2)
                    cout << " ";
                }
            cout << endl;
        }
    if(count == 9 && w1 == 0 && w2 == 0){
        cout << "It's a tie! No coins earned.\n";
            //cout << "Press any key to continue...\n";
            //count = 0;
           /* for (int i = 0 ; i <= 2 ; i++){
                for (int j = 0 ; j <= 2 ; j++)
                    map[i][j] = 0;
            }
            char a;
            a = getche();
            system("cls");*/
    }    
    else if(w1 == 1){
        cout << "You win!" << endl;
        cout << "Gain 100 coins." << endl;
        bal += 100;
    }
    else if (w2 == 1){
        cout << "You lose!" << endl;
        cout << "No coins earned." << endl;
    }
    cout << "Press any key to continue..." << endl;
    char a = getch();
    
}
void bingo(int &bal){
    system("cls");
	srand(time(NULL));
	vector<int> map(25,0),numbers(100,0),call(100,0);
	int is_counted[25] = {0};
	for(int i = 0 ; i < 100 ; i++){
        numbers[i] = i + 1;
        call[i] = i + 1;
    }
	random_shuffle(numbers.begin(),numbers.end());
    random_shuffle(call.begin(),call.end());
	for(int i = 0 ; i < 25 ; i++)
		map[i] = numbers[i];
	cout << "Here's your bingo card:" << endl;
	for(int i = 0 ; i < 5 ; i++){
		for (int j = 0 ; j < 5 ; j++)
			cout << map[5*i+j] << "\t";
		cout << endl;
	}
	cout << "The computer will now start calling numbers." << endl;
	cout << "If a number is on your bingo card, it will be marked." << endl;
	for(int num = 0 ; num < 50 ; num++){
		cout << num + 1 << " Number called: " << call[num] << endl;
		for(int s = 0 ; s < 25 ; s++){
			if(call[num] == map[s]){
				is_counted[s] = 1;
				break;
			}
		}
		for(int i = 0 ; i < 5 ; i++){
			for (int j = 0 ; j < 5 ; j++){
				if(is_counted[5*i+j] == 0)
					cout << map[5*i+j];
				else
					cout << "*";
				cout << "\t";
			}
			cout << endl;
		}
		int wincol , winrow , winlu = 0 , winru = 0;
		for(int i = 0 ; i < 5 ; i++){
			wincol = 0;
			winrow = 0;
			for(int j = 0; j < 5 ; j++){
				wincol += is_counted[5*i+j];
				winrow += is_counted[5*j+i];
			}
			if(wincol == 5 || winrow == 5)
				break;
			winlu += is_counted[6*i];
			winru += is_counted[4+4*i];
		}
		char anykey;
		if(wincol == 5 || winrow == 5 || winlu == 5 || winru == 5){
			cout << "BINGO!" << endl;
			cout << "You got bingo." << endl;
			cout << "Gain 100 coins." << endl;
            bal += 100;
			cout << "Press any key to return to menu..." << endl;
			anykey = getch();
			break;
		}		
		cout << "Press any key to continue..." << endl;
		anykey = getch();
		if(num == 49){
			cout << "You didn't got bingo :(" << endl;
			cout << "You lost 100 coins." << endl;
            bal -= 100;
			cout << "Press any key to return to menu..." << endl;
			anykey = getch();		
		}
	}
}

void dancesimulator(int &bal){
    srand(time(NULL));
    int score = 0;
    ifstream song;  
    //string s[2] = {"──────────────────────────／一＼───","──────────────────────────＼一／───"};
    string s[3] = {"-------------------------/-\\----","                                ","-------------------------\\-/----"};//25,27,31
    string judge[3] = {"perfect!","bad!","miss!"};
    char press[4] = {'w','s','a','d'};
    string arrow[4] = {"^","v","<",">"};
    int plus = 100;
    string play;
    int combo = 0;
    system("cls");
    cout << "Welcome to Dance Simulator!" << endl;
    cout << "If your score is more than 10000, then you'll get 100 coins." << endl;
    cout << "Press any key to start playing (use wasd to play)...";
    char get = getch();
    song.open("song.txt");
    if(!song.is_open()){
        cerr << "The song cannot be found." << endl;
        exit(1);
    }
    getline(song,play);
    for(char &i : play){
        if(i == '1'){
            int a = rand() % 4;
            i = press[a];
        }
    }
    string display;
    for(int i = 0 ; i < play.size() ; i++){
        if(play[i] == '0')
            display.append(" ");
        for(int j = 0 ; j < 4 ; j++){ 
            if (play[i] == press[j])
                display.append(arrow[j]);
        }
    }
    //cout << endl << play << endl;
    //cout << display << endl;
    //system("pause");
    string done = " ";
    string actual = "                                ";
    for(int i = 0 ; i < play.size() ; i++){
        system("cls");
        s[1].pop_back();
        actual.pop_back();
        if(play[i] != '0'){
            s[1].insert(s[1].begin(),display[i]);
            actual.insert(actual.begin(),play[i]);
        }
        else{
            s[1].insert(s[1].begin(),' ');   
            actual.insert(actual.begin(),' '); 
        }
        for(int j = 0 ; j < 3 ; j++)
            cout << s[j] << endl;
        //cout << actual << endl;
        cout << endl << "Score:" << score << endl;
        cout << "\n\nCombo:" << combo << endl << done << endl;
        if(actual[26]!=' '){
            get = getch();
            if(get == actual[26]){
                done = judge[0];
                s[1][26] = ' ';
                combo++;
                score += (combo/10 + 1) *plus;             
            }
            else{
                done = judge[2];
                combo = 0;
            }
        }
        else{
            Sleep(100);
        }
    }
    system("cls");
    cout << "Your score is : " << score << endl;
    if(score >= 10000){
        cout << "Congratulations!  You earned 100 coins!" << endl;
        bal += 100;
    }
    else
        cout << "It's a pity! you haven't reach 10000 scores.  No coins earned." << endl;
    cout << "Press any key to return to menu..." << endl;
    get = getch();
}
void menu(string &acc , int &bal , int &option){
    char c,num = 1;
    option = 0;
    string m[5]={"Tic Tac Toe","Bingo","Dance Simulator", "Change User" , "Exit"};
    while(1){
        system("cls");
        cout << "Hi " << acc << endl;
        cout << "Welcome to the Funland Game Center!\n";
        cout << "You have " << bal << " coins\n";
        cout << "Please select a game:\n";
        for(int i = 0 ; i <= 4 ; i++){
            if(i == option)
            cout << "> ";
            else
            cout << "  ";
            cout << m[i] << endl;
        }
        c = getch();
        if(c == 'w' || c == 'W'){
            option--;
            if(option == -1)
            option = 4;
        }
        else if(c == 's' || c == 'S'){
            option++;
            if(option == 5)
            option = 0;
        }
        else if(c == '\r')
            break;
        else
            continue;
    }
}
void save(fstream &log ,string &acc, int &bal){
    stringstream ss;
    string s,tempacc,temppw;
    int tempbal; 
    vector<string> account;
    log.clear();
    log.seekg(0,ios::beg);
    while(getline(log,s))
        account.push_back(s);
    for(int i = 0 ; i < account.size() ; i++){
        ss.str("");
        ss.clear();
        ss << account[i];
        ss >> tempacc >> temppw >> tempbal;
        if(acc == tempacc){
            account[i] = tempacc + " " + temppw + " " + to_string(bal);
            cout << "saving..." << endl;
            break;
        }
    }
    log.close();
    log.open("account.txt", ios::in | ios::out |ios::trunc);
    for(string &line : account){
        //cout << line << endl;
        log << line << endl;
    }
}
