#include <iostream>

using namespace std;

enum enQuestionLevel { Easy = 1, Mediume = 2, Hard = 3, Mix = 4 };

enum enOprationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOpt = 5 };

struct stQuestioninfo
{
    int QuesNumber = 0;
    enQuestionLevel Queslevel;
    enOprationType OptType;
    int Result = 0;
    int Answer = 0;
    bool CheckResult = true;
};

struct stGameResults
{
    string FinalResult = "";
    int NumberOfQues = 0;
    string QuestionsLevel = "";
    string OpType = "";
    int RightAnswer = 0;
    int WrongAnswer = 0;

};

short ReadNumber(string Mesege)
{
    short Number = 0;

    cout << Mesege;
    cin >> Number;

    return Number;
}

enQuestionLevel ReadQuestionLevel()
{
    short Number = 0;
    do
    {
        cout << "Enter Question level [1] Esay, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> Number;

    } while (Number < 1 || Number > 4);
    
    return (enQuestionLevel)Number;
}

enOprationType ReadOprationType()
{
    short Number = 0;
    do
    {
        cout << "Enter opration type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> Number;

    } while (Number < 1 || Number > 5);

    return (enOprationType)Number;
}

int RandomNumber(int From, int To)
{
    int RandNumber = rand() % (To - From + 1) + From;
    return RandNumber;
}

string strQueslevel(enQuestionLevel Level)
{
    string strLevel[4] = { "Easy","Mediume","Hard","Mix" };
    return strLevel[Level - 1];
}

string strOprationType(enOprationType Opration)
{
    string strLevel[5] = { "+","-","*","/","Mix" };
    return strLevel[Opration - 1];
}

int NumberInlevel(enQuestionLevel level)
{
    
    switch (level)
    {
    case Easy:
        return RandomNumber(1, 10);
        break;
    case Mediume:
        return RandomNumber(11, 50);
        break;
    case Hard:
        return RandomNumber(51, 100);
        break;
    case Mix:
        return RandomNumber(1, 100);
        break;
    }
    
}

int Calculator(int Number1, int Number2, enOprationType Opration)
{
    int Result = 0;
    switch (Opration)
    {
    case Add:
    {
        cout << Number1 << endl;
        cout << Number2 << "  +\n\n";
        cout << "--------------\n";
        Result = Number1 + Number2;
        return Result;
    }
    case Sub:
    {
        cout << Number1 << endl;
        cout << Number2 << "  -\n\n";
        cout << "--------------\n";
        Result = Number1 - Number2;
        return Result;
    }
    case Mult:
    {
        cout << Number1 << endl;
        cout << Number2 << "  *\n\n";
        cout << "--------------\n";
        Result = Number1 * Number2;
        return Result;
    }
    case Div:
    {
        cout << Number1 << endl;
        cout << Number2 << "  /\n\n";
        cout << "--------------\n";
        Result = Number1 / Number2;
        return Result;
    }
    }
    
}

enOprationType MixOp()
{
    return (enOprationType)RandomNumber(1, 4);
}

int CalculatOpResult(enOprationType opration, enQuestionLevel level)
{   
    int Result = 0;

    if (opration == enOprationType::MixOpt)
        return Calculator(NumberInlevel(level), NumberInlevel(level), MixOp());
    
    else
        return Calculator(NumberInlevel(level), NumberInlevel(level), opration);

}

bool TrueOrFalseAnswer(stQuestioninfo QuesInfo)
{
    if (QuesInfo.Result == QuesInfo.Answer)
        return true;
    else
        return false;
}

stGameResults FillGameResult(string FinalResult, short NumOfQues, string QuesLevel,string Opration,short RightAnsewr,short WrongAnswer)
{
    stGameResults GameResults;

    GameResults.NumberOfQues = NumOfQues;
    GameResults.QuestionsLevel = QuesLevel;
    GameResults.OpType = Opration;
    GameResults.RightAnswer = RightAnsewr;
    GameResults.WrongAnswer = WrongAnswer;
    GameResults.FinalResult = FinalResult;
    return GameResults;
    
}

void PrintQuesResult(stQuestioninfo QuesInfo)
{
    if (QuesInfo.CheckResult)
    {
        cout << "\nRight Answer :-)\n";
        system("color 2F");
        
    }
    else
    {
        cout << "\nWrong Answer :-(\n";
        cout << "The right answer is: " << QuesInfo.Result << "\n\n";
        system("color 4F");
        cout << "\a";
    }
}

stGameResults PlayGame(int NumberOfQues)
{
    short RightAnswer = 0, WrongAnswer = 0;
    string FinalResult = "";
    stQuestioninfo QuesInfo;

    QuesInfo.Queslevel = ReadQuestionLevel();
    QuesInfo.OptType = ReadOprationType();

    for (int Ques = 1; Ques <= NumberOfQues; Ques++)
    {
        QuesInfo.QuesNumber = Ques;
        
        cout << "\nQuestion [" << QuesInfo.QuesNumber << "/" << NumberOfQues << "]\n\n";

        QuesInfo.Result = CalculatOpResult(QuesInfo.OptType, QuesInfo.Queslevel);
        QuesInfo.Answer = (enQuestionLevel)ReadNumber("");
        QuesInfo.CheckResult = TrueOrFalseAnswer(QuesInfo);
        
        if (QuesInfo.CheckResult)
            RightAnswer++;
        else
            WrongAnswer++;

        if (RightAnswer >= WrongAnswer)
            FinalResult = "PASS :-)";
        else
            FinalResult = "Fail :-(";

   
        PrintQuesResult(QuesInfo);

    }
    return FillGameResult(FinalResult, NumberOfQues, strQueslevel(QuesInfo.Queslevel), strOprationType(QuesInfo.OptType), RightAnswer, WrongAnswer);
}

void PrintGameResults(stGameResults GameResults)
{
    cout << "\n\n--------------------------------------------------\n\n";
    cout << "  Final Results is " << GameResults.FinalResult;
    cout << "\n\n--------------------------------------------------\n";
    
    cout << endl;
    cout <<"Number of Question: " << GameResults.NumberOfQues << endl;
    cout <<"Question level    : " << GameResults.QuestionsLevel << endl;
    cout <<"OpType            : " << GameResults.OpType << endl;
    cout <<"Number of Right Answers: " << GameResults.RightAnswer << endl;
    cout <<"Number of Wrong Answers: " << GameResults.WrongAnswer << endl;

    cout << "\n--------------------------------------------------\n";
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    stGameResults GameResults;
    do
    {
        ResetScreen();

        GameResults = PlayGame(ReadNumber("How many Questions do you want answer ? "));
        PrintGameResults(GameResults);
        
        cout << "Do you want Play Again ? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    
    StartGame();
    return 0;
}
