#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <conio.h>
using namespace std;

char menu()
{
    bool menuLoop=true;
    do{
        system("cls");
        cout << "=================\n";
        cout << "Projekt \n";
        cout << "=================\n";
        cout << "Wybierz którąś opcję z poniższej listy: \n";
        cout << "1) WORDLE \n";
        cout << "2) Instrukcje \n";
        cout << "3) Wyjdź \n";
        switch(getch())
        {
            case '1':
            return '1';
            case '2':
            return '2';
            case '3':
            return '3';
            default:
            break;
        }

    }while(menuLoop==true);
}

void instrukcje()
{
    system("cls");
    cout << "=================\n";
    cout << "WORDLE\n";
    cout << "=================\n";
    cout << "Zgadnij pięcio-literowe słowo. \n";
    cout << "Masz 6 prób. Każda niezużyta próba zostaje punktem po zgadnięciu słowa. \n";
    cout << "Każda nieudana próba podpowie ci jakie litery, które użyłeś w próbie są w słowie. \n";
    cout << "Backspace usuwa niepożądane litery. \n";
    getch();
}

void gra()
{
    {
        bool mainLoop,gameLoop,typeLoop,confirmLoop,endLoop,sessionLoop;
        int punkty,liczbaprob=0;
        char slowo[5],proba[5],klucz[5];
        
        //deklaracje potrzebne do wczytania plików
        int line_number=0,max_slowek=0,kursor=0;
        string line;
    
        //deklaracje potrzebne do zapisania rekordów
        ofstream outfile;
        string nick;
        
        system("cls"); //check czy plik ze słowami się wczytał czy nie
        ifstream file("./wordle/wordle_slowa.txt");
        if (file.fail())
        {
            cout << "Nie udało się wczytać zbioru słów. Sprawdź, czy istnieje plik ./wordle/wordle_slowa.txt" << endl;
        }else{
            cout << "Wczytywanie pliku ze słowami powiodło się." << endl; 
            while (!file.eof())
            {
                max_slowek++;
                getline(file,line);
            }
            cout << "Plik ma: " << max_slowek << " słówka" << endl; //wyliczanie słów w pliku
        }
        file.close();
        getch();
    
        system("cls"); //check czy plik z rekordami się wczytał czy nie
        ifstream file2("./wordle/wordle_rekordy.txt");
        if (file2.fail())
        {
            cout << "Nie udało się wczytać rekordów. Sprawdź, czy istnieje plik ./wordle/wordle_rekordy.txt" << endl;
        }else{
            cout << "Wczytywanie pliku z rekordami powiodło się."; 
        }
        file2.close();
        getch();
        
        mainLoop=true;
        do//mainLoop
        {
                punkty=0;
                system("cls");
                cout << "============================\n";
                cout << "Wordle \n";
                cout << "============================\n";
                cout << "Wybierz którąś opcję z poniższej listy: \n";
                cout << "1) Zacznij grę \n";
                cout << "2) Rekordy \n";
                cout << "3) Wróć \n";
                switch (getch())
                {
                    case '1': // start sesji // sessionLoop
                    sessionLoop=true;
                    do
                    { //reset prób i wczytywanie losowego słowa
                        liczbaprob=6; 
                        line_number = rand()%max_slowek+1;
                        kursor=0;
                        
                        for(int i=0;i<5;i++)
                        {
                            slowo[i]=NULL;
                        }
    
                        file.open("./wordle/wordle_slowa.txt");
                        while (!file.eof())
                        {
                            kursor++;
                            getline(file,line);
                            if (kursor==line_number) break;
                        }
                        strcpy(slowo,line.c_str()); //zamienia string 'line' w char array 'slowo'
                        file.close();
                
                        gameLoop=true;
                        do //gameLoop START
                        {
                        typeLoop=true;
                        do //typeLoop START
                        {
                            for(int i=0;i<5;i++)
                            {
                                klucz[i] = false;
                            }
                            for(int i=0;i<5;i++)
                            {
                                proba[i]=NULL;
                            }
                            for(int i=0;i<5;i++)
                            {
                                if(i<0)
                                {
                                    i++;
                                }
                                system("cls");
                                cout << "punkty w tej sesji: " << punkty << endl;
                                cout << "========================" << endl;
                                cout << "próba: " << liczbaprob << endl;
                                cout << "========================" << endl;
                                cout << "litera " << i + 1 << ":" << endl;
                                cout << proba[0] << proba[1] << proba[2] << proba[3];
                                proba[i] = getch();
                                if(proba[i]=='\b')
                                {
                                    proba[i]=NULL;
                                    proba[i-1]=NULL;
                                    i-=2;
                                }
                                proba[i] = tolower(proba[i]);
                            }
                            confirmLoop=true;
                            do{ //confirmLoop START
                                system("cls");
                                for(int i=0;i<5;i++)
                                {
                                    cout << proba[i];
                                }
                                cout << endl;
                                cout << "Wciśnij 't' aby zatwierdzić decyzję. \n";
                                cout << "Wciśnij 'n' aby wpisać ponownie. \n";
                                switch(getch())
                                {
                                    case 't':
                                        confirmLoop=false;
                                        typeLoop=false;
                                        break;
                                    case 'n':
                                        confirmLoop=false;
                                        break;
                                    default:
                                        confirmLoop=true;
                                        break;
                                }
                            }while(confirmLoop); // koniec confirmLoop
                        } while (typeLoop);
                        // koniec typeLoop
                        
                        for(int i=0;i<5;i++) //Sprawdzanie próby
                        {
                            for(int j=0;j<5;j++)
                            {
                                if(proba[i]==slowo[j])
                                {
                                    if(i==j)
                                    {
                                        klucz[i]=true;
                                        cout << "litera " << proba[i] << " jest na miejscu " << j+1 << endl;
                                    }else
                                    {
                                        cout << "litera " << proba[i] << " jest gdzieś w słowie." << endl;
                                    }
                                }
                            }
                        }
    
                        endLoop=true;
    
                        if(klucz[0]==true&&klucz[1]==true&&klucz[2]==true&&klucz[3]==true&&klucz[4]==true)
                        {
                            punkty+=liczbaprob;
                            do
                            {
                                    system("cls");
                                    cout << "Zgadłeś słowo! Dostałeś " << liczbaprob << " punktów! \nMasz teraz " << punkty << " punktów! Czy zagrasz dalej?" << endl;
                                    cout << "Wciśnij 't' aby grać dalej i 'n' aby przerwać grę."<< endl;
                                    switch(getch())
                                    {
                                        case 't':
                                            gameLoop = false;
                                            endLoop=false;
                                            break;
                                        case 'n':
                                            endLoop=false;
                                            gameLoop=false;
                                            sessionLoop=false;
                                            system("cls");
                                            outfile.open("./wordle/wordle_rekordy.txt",ios::app);
                                            if(outfile.fail())
                                            {
                                                cout << "Nie można zapisać rekordów! Sprawdź, czy plik ./wordle/wordle_rekordy.txt istnieje.";
                                                getch();
                                            }else
                                            {
                                                cout << "Wczytywanie pliku z rekordami powiodło się." << endl;
                                                getch();
                                                system("cls");
                                                cout << "Wpisz swoje imię: ";
                                                getline(cin,nick);
                                                outfile << nick << " / " << punkty << " pkt" << endl;
                                            }
                                            outfile.close();
                                            break;
                                        default:
                                            break;
                                    }
                            }while(endLoop);
                        }else
                        {
                            liczbaprob-=1;
                                cout << "Masz jeszcze " << liczbaprob << " prób.";
                                getch();
                                if(liczbaprob==0)
                                {
                                    do{
                                        system("cls");
                                        cout << "Przegrałeś! Słowem było: ";
                                        for(int i=0;i<5;i++)
                                        {
                                            cout << slowo[i];
                                        }
                                        cout << endl << "Czy chciałbyś spróbować ponownie? Twoje punkty zostaną zresetowane do zera." << endl;
                                        cout << "Wciśnij 't' aby zacząć od nowa i 'n' aby przerwać grę i zapisać wynik."<< endl;
                                        switch(getch())
                                        {
                                            case 't':
                                                punkty=0;
                                                endLoop=false;
                                                gameLoop = false;
                                                break;
                                            case 'n':
                                                endLoop=false;
                                                gameLoop=false;
                                                sessionLoop = false;
                                                outfile.open("./wordle/wordle_rekordy.txt",ios::app);
                                                if(outfile.fail())
                                                {
                                                    cout << "Nie można zapisać rekordów! Sprawdź, czy plik ./wordle/wordle_rekordy.txt istnieje.";
                                                }else
                                                {
                                                    cout << "Wczytywanie pliku z rekordami powiodło się." << endl;
                                                    getch();
                                                    system("cls");
                                                    cout << "Wpisz swoje imię: ";
                                                    getline(cin,nick);
                                                    outfile << nick << " / " << punkty << " pkt" << endl;
                                                }
                                                outfile.close();
                                                break;
                                            default:
                                                break;
                                        }
                                    }while(endLoop);
                                }
                        }
                        }while(gameLoop);     
                    }while(sessionLoop);
                    break;
                    case '2':
                    system("cls");
                    file2.open("./wordle/wordle_rekordy.txt");
                    cout << file2.rdbuf();
                    file2.close();
                    getch();
                    break;
                    case '3':
                    mainLoop=false;
                    break;
                    default:
                    break;
                }
            }while(mainLoop);
    }    
}

main()
{
    setlocale(LC_ALL,"pl_PL.UTF-8");
    srand(time(NULL));
    bool mainLoop=true;
    do{
        switch(menu())
        {
            case '1':
            gra();
            break;
            case '2':
            instrukcje();
            break;
            case '3':
            mainLoop=false;
            break;
            default:
            break;
        }
    }while(mainLoop==true);
}