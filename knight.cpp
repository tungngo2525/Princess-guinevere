#include "knight.h"
// Anh Nguyen : 2/3 - 12:30
//--------------------------
void initStatus(string line , int *wordlst){
    int index = 0;
    int tmp;
    stringstream abc(line);
    while(abc >> tmp){ 
        wordlst[index] = tmp;
        index++;
    };
}
bool primeNum(int num){
    bool flag = true;
    if (num <2) return flag = false;
    int i = 2;
    while(i <num){
        if( num%i==0 ) {
            flag = false;
            break;
        }
        i++;
    }
    return flag;
}
int makedmg(int id, int lvl){
    double bdmg;
    switch (id)
    {
        case 1:
            bdmg = 1;
            break;
        case 2:
            bdmg = 1.5;
                break;
        case 3:
            bdmg = 4.5;
            break;
        case 4:
            bdmg = 7.5;
            break;
        case 5:
            bdmg = 9.5;
            break;
        default:
            bdmg = 0;
            break;
    }
    return int(bdmg * double(lvl) * 10);
}
void useitem_16(
    int &HP,
    int &maxHP,
    int &item_16,
    int &curse6,
    int &curse7,
    int &lvl,
    int &lvlpre1
)
{
    item_16--;
    HP = maxHP;
    curse6 = 0;
    if(curse7 > 0)
    {
        curse7 = 0;
        lvl = lvlpre1;
    }
}
void takeDamge(
    int &HP,
    int &maxHP,
    int &item_16,
    int &curse6,
    int &curse7,
    int &lvl,
    int &lvlpre1, 
    int damge, 
    int &rescue
    )
{
    HP -= damge;
    if(HP <= 0 )
    {
        if(item_16 > 0)
        {
            useitem_16(
                HP,
                maxHP,
                item_16,
                curse6,
                curse7,
                lvl,
                lvlpre1
            );
        }
        else rescue = 0;
    }
}

int fibonacci(int n)
{
  if (n == 0 || n == 1)
    return n;
  else
    return (fibonacci(n-1) + fibonacci(n-2));
}


void getAray(string filenamne, int line, char delim, int &size, int *wordlst){
    string tmps, c;
    int i = 0;
    ifstream file;
    file.open(filenamne);
        while (i < line) {
            getline(file, tmps);
            i++;
        }
        int j = 0;
        while(getline(file, c, delim)){
            stringstream abc(c);
            abc >> wordlst[j]; 
            j++;
        }
        wordlst[j] = '\0';
        size = j;
    file.close();
}

int getInt(string filenamne, int line){
    int num = 0;
    string tmps, line_1;
    int i = 0;
    ifstream file;
    file.open(filenamne);
        while (i < line) {
            getline(file, tmps);
            i++;
        }
        getline(file, line_1);
        stringstream abc(line_1); 
        abc >> num;
    file.close();
    return num;
}

int func1(int n, int *wordlst,int m){
    //m = 1 vi tri thu 2
    // m = 0 vi tri dau tien
    int max = wordlst[0];
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
        if(m == 1){
            if(max <= wordlst[i]) {
                max = wordlst[i];
                pos = i;
            }
        }
        else if(m == 0){
            if(max < wordlst[i]) {
                max = wordlst[i];
                pos = i;
            }
        }

    }
    return pos;  
}

int func2(int n, int *wordlst,int m){
    int min = wordlst[0];
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
        if(m == 1){
            if(min >= wordlst[i]) {
                min = wordlst[i];
                pos = i;
            }
        }
        else if(m == 0){
            if(min > wordlst[i]) {
                min = wordlst[i];
                pos = i;
            }
        }
    }
    return pos;  
}

void func3(int n, int *wordlst, int &mtx, int &mti){
    int tmp = 0;
    int tmpcur = 0;
    bool Mnumber = false,
    changeDirect = false,
    endPoint = false;
    for (int i = 1; i < n; i++)
    {
        if( wordlst[i-1] < wordlst[i]){
            tmp = 1;
            if(tmpcur == 0)
                tmpcur = 1;
            else
            {
                if(tmpcur == -1)
                    break;
            }

        }
        else if(wordlst[i-1] > wordlst[i]){
            if(tmpcur == 0){
                tmp = -1;
                tmpcur = -1;
            }
            else{
                if(tmpcur == 1)
                {
                    if(!changeDirect)
                    {
                        changeDirect = true;
                        tmp = -1;
                        tmpcur = -1;
                        mtx = wordlst[i-1];
                        mti = i-1;
                    }else
                        break;
                }
            }
        }
        else if(wordlst[i-1] == wordlst[i]){
            break;
        }
        if(i == n -1) endPoint = true;
    }
    if(endPoint){
        if(!changeDirect){
            if(tmp == 1) {
                mtx = wordlst[n-1];
                mti = n-1;
            }
            else if(tmp == -1) {
                mtx = wordlst[0]; 
                mti = 0;
            }  
        }
        Mnumber = true;
    }
    if(Mnumber == false) mtx = -2, mti = -3;
}

void changewordlst(int n, int *wordlst,int &max, int &min){
    int wordlstAfter[n+1];
    int tmp;
    for (int i = 0; i < n; i++)
    {
        tmp = wordlst[i];
        if(tmp < 0) tmp = -tmp;
        wordlstAfter[i] = ( 17 *  tmp + 9 ) % 257;
    }
    wordlstAfter[n] = '\0';
    max = func1(n, wordlstAfter,0);
    min = func2(n, wordlstAfter,0);
}

void func4(int n, int *wordlst,int &max, int &pos){
    int e = n;
    if(n > 3) e = 3;
    int wordlst2[e+1];
    int tmp;
    for (int i = 0; i < e; i++)
    {
        tmp = wordlst[i];
        if(tmp < 0) tmp = -tmp;
        wordlst2[i] = ( 17 *  tmp + 9 ) % 257;
    }
    int maxi1 = func1(e, wordlst2,1);
    max = 0;
    pos = maxi1;
    for (int i = 0; i < n && i < 3; i++)
    {
        if(max < wordlst2[i] && i != maxi1) {
            max = wordlst2[i];
            pos = i;
        }
    };
    if(n <= 1 || (pos == maxi1)){
        max = -5;
        pos = -7;
    };
}

void mushGhost(string path,
    int event,
    int &HP,
    int &maxHP,
    int &item_16,
    int &curse6,
    int &curse7,
    int &lvl,
    int &lvlpre1, 
    int &rescue
    )
{
    string eventstr = to_string(event);
    int size = eventstr.length() - 2;
    char arr[ size + 1 ];
    int numSize;
    string line1,line2;
    ifstream file;
    file.open(path);
    getline(file, line1);
    getline(file, line2);
    file.close();
    stringstream abc(line1);
    abc >> numSize;
    int wordlst[numSize+1];
    for (int i = 0; i < size; i++)
    {
        arr[i] = eventstr[i+2];
    }
    int tm = 0;
    int index = 0;
    string item;
    stringstream abc1(line2);
    while(getline(abc1,item,',')){
        stringstream abc2(item);
        abc2 >> wordlst[index];
        index++;
    }
    for (int i = 0; i < size; i++)
    {
        if(arr[i] == '1') {
            takeDamge(
                HP,
                maxHP,
                item_16,
                curse6,
                curse7,
                lvl,
                lvlpre1, 
                func1(numSize,wordlst,1) + func2(numSize,wordlst,1),
                 rescue
                 );
        }
        else if (arr[i] == '2') {
            int mtx,mti;
            func3(numSize, wordlst, mtx, mti);
            takeDamge(HP,maxHP,item_16,curse6, curse7,lvl,lvlpre1, 
            mtx + mti, 
            rescue);
        }
        else if (arr[i] == '3') {
            int maxx, minx;
            changewordlst(numSize, wordlst,maxx,minx);
            takeDamge(HP,maxHP,item_16,curse6,curse7,lvl,lvlpre1,
            maxx + minx, 
            rescue);
        }
        else if (arr[i] == '4') { 
            int max2,pos2;
            func4(numSize, wordlst, max2,pos2);
            takeDamge(HP,maxHP,item_16,curse6,curse7,lvl,lvlpre1,
            max2 + pos2, 
            rescue);
        }
        if(rescue == 0) break;
    }
}

void event15_17(
    int &HP,
    int &maxHP, 
    int &item_14,
    int &item_15,
    int &item_16,
    int &curse6,
    int &curse7,
    int &lvl,
    int &lvlpre1,
    int idItem
    )
{
    if(idItem == 15){
        if( curse6 > 0) 
        {
            curse6 = 0;      
            HP *= 5;
            if(HP > maxHP) HP = maxHP;
        }
        else {
            if(item_14 < 99) 
                item_14 += 1;
        }
    }
    else if(idItem == 16){
        if(curse7 > 0)
        {
            curse7 = 0;
            lvl = lvlpre1;
        }   
        else {
            if(item_15 < 99) 
                item_15 += 1;
        }
    }
    else if(idItem == 17){
        if(item_16 < 99) 
            item_16 += 1;
    }
}

bool m1(string str)
{
    if(str.length() < 6 ) return false;
    int size = str.length();
    for (int i = 0; i < size; i++)
    {
        if(i + 6 >= size) 
            return false;
        if( (str[i] == 'M' || str[i] == 'm' ) && str[i+1] == 'e' && str[i+2] == 'r' && str[i+3] == 'l' && str[i+4] == 'i' && str[i+5] == 'n' )
            return true;
    }
    return false;
}

bool m2(string str)
{
    int m = 0,
    e = 0, 
    r = 0, 
    l = 0, 
    i = 0, 
    n = 0;
    int size = str.length();
    for (int j = 0; j < size; j++)
    {
        char c = str[j];
        if(c == 'M' || c == 'm') m++;
        else if( c == 'e' || c == 'E') e++;
        else if(c == 'R' || c == 'r') r++;
        else if (c == 'L' || c == 'l') l++;
        else if (c == 'I' || c == 'i') i++;
        else if (c == 'N' || c == 'n') n++;
    }
    return m > 0 && e > 0 && r > 0 && l > 0 && i > 0 && n >0;
    
}

void meetEvent18(
    int &HP,
    int &maxHP, 
    int &item_14,
    int &item_15,
    int &item_16,
    int &curse6,
    int &curse7,
    int &lvl,
    int &lvlpre1,
    string filename
    )
{
    int r1 = getInt(filename, 0),
        c1 = getInt(filename, 1),
        line = 2, row = 0, col = 0, size,
        wordlst[r1 + 1][c1 + 1];
    for (int i = 0; i < r1; i++)
    {
        getAray(filename, line + i, ' ', size, wordlst[i]);
    }
    int n;
    for (int i = 0; i < r1; i++)
    {
        n = 0;
        for (int j = 0; j < c1; j++)
        {
            if(wordlst[i][j] >= 16 && wordlst[i][j] <= 18 && n < 3)
            {
                event15_17(HP,maxHP, item_14,item_15,item_16,curse6,curse7,lvl,lvlpre1, wordlst[i][j] - 1);
                n++;
            }
        }
    }
}

void meetEvent19(
    string filename, 
    int &HP,
    int &maxHP,
    bool &event19
    )
{
    //TODO
    if(event19==false){
        event19 = true;
        string tmp;
        int size = getInt(filename,0);
        string str[size + 1];
        int index=0;
        ifstream file;
        file.open(filename);
            getline(file, tmp);
            while (getline(file, tmp)) {
                str[index] = tmp;
                index++;
            }
        file.close();
        for (int i = 0; i < size; i++)
        {
            if(m1(str[i])) HP += 3;
            else{
                if(m2(str[i])) HP +=2;
            }
            if(HP > maxHP) 
                HP = maxHP;
        }
    } 
}

void Bowser(
    bool &king999,
    bool &primeObject,
    int &lvl, 
    int event, 
    int &rescue
    )
{
    if(king999 ||(primeObject && lvl >= 8) || lvl == 10) 
        lvl = 10;
    else
        rescue = 0;
}
//------------------------

void display(
    int HP,
int lvl,
int item_14,
int item_15,
int item_16, 
int rescue
)
{
    cout << "HP=" << HP
        << ", level=" << lvl
        << ", remedy=" << item_14
        << ", maidenkiss=" << item_15
        << ", phoenixdown=" << item_16
        << ", rescue=" << rescue << endl;
}


void adventureToKoopa(
    string file_input, 
    int & HP, 
    int & level, 
    int & item_14, 
    int & item_15, 
    int & item_16, 
    int & rescue
    ) 
    {
    string line1, 
    line2, 
    line3;
    ifstream myfile(file_input);
    if (myfile.is_open()) {
        getline(myfile,line1);
        getline(myfile,line2);
        getline(myfile,line3);
        string file1_path = "";
        string file2_path = "";
        string file3_path = "";

        int iEvent[100], 
        nEvent = 0, 
        rescue = -1;
        int HP; 
        int maxHP; 
        int level; 
        int item_14; 
        int item_15; 
        int item_16; 
        int lvlpre1; 
        int curse6 = 0; 
        int curse7 = 0; 
        bool event18 = false; 
        bool event19 = false; 
        bool king999 = false; 
        bool primeObject = false;
        int wordlst[5];
        initStatus(line1,wordlst);
        HP = wordlst[0]; ;
        maxHP = wordlst[0]; 
        level = wordlst[1]; 
        item_14 = wordlst[2]; 
        item_15 = wordlst[3]; 
        item_16 = wordlst[4];
        if( HP == 999) 
            king999 = true;
        else if(primeNum(HP)) 
            primeObject = true;
        ////
        int a;
        int index = 0; 
        stringstream abc(line2); 
        while(abc >> a){ 
            iEvent[index] = a; 
            index++; 
            nEvent++; 
        }; 

        int packIndex = 0;
        index = 0;
        while(line3[index] != '\0') { 
            if(line3[index] == ',') 
                packIndex++; 
            else{ 
                if(packIndex == 0) 
                    file1_path += line3[index]; 
                else if(packIndex == 1) 
                    file2_path += line3[index]; 
                else 
                    file3_path += line3[index]; 
            }
            index++; 
        };

        /////
        int i = 0;
        while(true){
            if(iEvent[i] == 0 )
            {
                rescue = 1;
                display(HP,level,item_14,item_15,item_16, rescue);
                break;
            }
            else
            {
                if(iEvent[i] > 0 && iEvent[i] <= 5)
                {
                    int b = (i+1) % 10;
                    int lvl = i > 6?(b > 5?b : 5) : b;
                    if(level > lvl || king999 == true || primeObject == true){
                        level += 1;
                        if( level > 10 ) level = 10;
                    }
                    else if (level < lvl)
                        takeDamge(HP,maxHP,item_16,curse6,curse7,level,lvlpre1, makedmg(iEvent[i],lvl), rescue);
                }
                else if(iEvent[i] == 6)
                {
                    if(curse6 == 0 || curse7 == 0){
                    int b = (i+1) % 10;
                    int lvl = i > 6?(b > 5?b : 5) : b;
                    if(level > lvl || king999 == true || primeObject == true) 
                    {
                        level += 2;
                        if( level > 10 ) level = 10;
                    }
                    else if(level < lvl)
                    {
                        if(item_14 <= 0){
                            curse6 = 4;
                            if(HP < 5)  
                                takeDamge(HP,maxHP,item_16,curse6,curse7,level,lvlpre1, 1, rescue);
                                
                            else 
                               
                                 double HP = floor(HP / 5);
                        } else{
                            item_14--;
                        }
                    }
                }
                }
                else if (iEvent[i] == 7)
                {
                    if(curse6 == 0 || curse7 == 0){
                    int b = (i+1) % 10;
                    int lvl = i > 6?(b > 5?b : 5) : b;
                    if(level > lvl || king999 == true || primeObject == true) 
                    {
                        level += 2;
                        if( level > 10 ) level = 10;
                    }
                    else if(level < lvl)
                    {
                        if(item_15 <= 0){
                            curse7 = 4;
                            lvlpre1 = level;
                            level -= 1;
                            if(level == 0) level = 1;
                        } else item_15--;
                    }
                }
                }
                else if(iEvent[i] == 11)
                    {
                        int n1 = ((level + item_16) % 5 + 1)*3;
                        int s1 = 0;

                        for (int i = 0; i < n1; i++)
                        {
                            s1 += 99 - (i * 2);
                        }

                        HP += (s1 % 100);

                        while (primeNum(HP) == false)
                        {
                            HP += 1;
                            if(HP >= maxHP) 
                                break;
                        };

                        if(HP > maxHP) 
                            HP = maxHP;
                    }
                else if(iEvent[i] == 12)
                {
                    int i = 1;
                    if(HP > 1){
                        while(fibonacci(i) < HP) 
                            i++;
                        HP = fibonacci(i-1);
                    }
                }
                else if(iEvent[i] == 13 || iEvent[i] >= 131)
                    mushGhost(file1_path,iEvent[i],HP,maxHP,item_16,curse6,curse7,level,lvlpre1, rescue);
                else if(iEvent[i] >= 15 && iEvent[i] <= 17)
                    event15_17(HP,maxHP, item_14,item_15,item_16,curse6,curse7,level,lvlpre1, iEvent[i]);
                else if(iEvent[i] == 18 )
                    meetEvent19(file3_path, HP,maxHP,event19);
                else if(iEvent[i] == 19 )
                {
                    if(event18 == false)
                    { 
                        event18 = true;
                        meetEvent18(HP,maxHP, item_14,item_15,item_16,curse6,curse7,level,lvlpre1,file2_path);
                    }  
                }
                else if(iEvent[i] == 99 )
                    Bowser(king999,primeObject,level, i,rescue);

                if( curse6 > 0) 
                {
                    curse6 -= 1;
                    if(curse6 == 0) {        
                        HP *= 5;
                        if(HP > maxHP) 
                            HP = maxHP;
                    }
                }
                if( curse7 > 0)
                {
                    curse7 -= 1;
                    if(curse7 == 0)
                       level = lvlpre1;
                }
                if(i == nEvent - 1)
                    rescue = 1;
                display(HP,
                level,
                item_14,
                item_15,
                item_16, 
                rescue
                );
                if(rescue == 0 || i == nEvent - 1)
                    break;
            }
            i++;
        }
    }
}