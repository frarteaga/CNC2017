/*
CNC 2017
2B checker
frankr@coj
*/

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-6;

int N, M, K;
vector<int> A;
vector<int> OfficialOutput;
vector<int> ContestantOutput;

void ShowUsage(){
    cout << "Usage: checker2b.exe <input> <official_output> <contestant_output>" << endl;
}

bool GetInput(string InFileName){
    ifstream fi(InFileName);

    if (fi.fail()){
        cerr << "Can not open input file" << endl;
        return false;
    }

    if (!(fi >> N >> M >> K)){
        cerr << "Not enough integers" << endl;
        return false;
    }

    for (int i = 0 ; i < N ; i++){
        int x;
        if (!(fi >> x)){
            cerr << "Not enough integers" << endl;
            return false;
        }
        A.push_back(x);
    }

    int dummy;
    if (fi >> dummy){
        cerr << "More data" << endl;
        return false;
    }

    fi.close();

    return true;
}

bool ReadKIntegersFrom(string FileName, vector<int>& V){
    ifstream f(FileName);

    if (f.fail()){
        cerr << "Can not open file " << FileName << endl;
        return false;
    }

    V.clear();
    int x;

    // K is a global var
    for (int i = 0 ; i < K ; i++){
        if (!(f >> x)){
            cerr << "Not enough integers" << endl;
            return false;
        }
        V.push_back(x);
    }

    int dummy;
    if (f >> dummy){
        cerr << "More data" << endl;
        return false;
    }

    f.close();

    return true;
}

bool ValidateMRestriction(const vector<int>& V){
    int minE = *min_element(V.begin(), V.end());
    // M is a global var
    if (minE < M){
        return false;
    }
    return true;
}

double GetLowestAverage(const vector<int>& V){
    double res = (LONG_MAX - 2);
    res *= res;
    int offset = 0;
    for(int c: V){
        long long sum = accumulate(A.begin() + offset, A.begin() + offset + c, 0LL);
        offset += c;
        double avg = (double)sum / (double)c;
        if (res > avg){
            res = avg;
        }
    }
    return res;
}

int main(int argc, char* argv[])
{
    /*
    if (argc != 4){
        ShowUsage();
        return 1;
    }
    */

    string InFileName = "dosb.in"; // string(argv[1]);
    string OfficialOutFileName = "dosb__ofi.out"; // string(argv[2]);
    string ContestantOutFileName = "dosb.out"; // string(argv[3]);

    bool noInputError = GetInput(InFileName);
    if (!noInputError){
        cout << "Check input file" << endl;
        //ShowUsage();
        return 1;
    }

    bool noOfficialOutError = ReadKIntegersFrom(OfficialOutFileName, OfficialOutput);

    if (!noOfficialOutError){
        cout << "Check official output file, do not contain exactly " << K << " integers" << endl;
        //ShowUsage();
        return 1;
    }

    bool noContestantOutError = ReadKIntegersFrom(ContestantOutFileName, ContestantOutput);

    if (!noContestantOutError){
        cout << "Contestant output do not contain exactly " << K << " integers" << endl;
        return 201; // WA
    }

    int sumOffcial = accumulate(OfficialOutput.begin(), OfficialOutput.end(), 0);

    if (sumOffcial != N){
        cout << "Check official output file, has not exactly N players" << endl;
        //ShowUsage();
        return 1;
    }

    int sumContestant = accumulate(ContestantOutput.begin(), ContestantOutput.end(), 0);

    if (sumContestant != N){
        cout << "Contestant solution has not exactly N players" << endl;
        return 201; // WA
    }

    bool MRestrictionOfficial = ValidateMRestriction(OfficialOutput);

    if (!MRestrictionOfficial){
        cout << "Check official output file, has a team with a fewer members than " << M << endl;
        //ShowUsage();
        return 1;
    }

    bool MRestrictionContestant = ValidateMRestriction(ContestantOutput);

    if (!MRestrictionContestant){
        cout << "Contestant solution has a team with a fewer members than " << M << endl;
        return 201; // WA
    }

    double officialSol = GetLowestAverage(OfficialOutput);
    double contestantSol = GetLowestAverage(ContestantOutput);

    if (fabs(contestantSol - officialSol) < EPSILON){
        cout << "Accepted" << endl;
        return 0; // AC
    }
    else{
        cout << "Jury average: " << officialSol << endl;
        cout << "Contestant average: " << contestantSol << endl;
        cout << "Wrong answer" << endl;
        return 201; // WA
    }

    return 1;
}

