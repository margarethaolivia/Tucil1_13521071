// #include <chrono>
// #include <cstdlib>
// #include <ctime>
// #include <iostream>
// #include <time.h>

#include <bits/stdc++.h>
using namespace std;

void display(vector<int> cards, char ops[], int pattern, int *count, vector<string> *sol)
{
    char buffer[25];

    switch (pattern)
    {
    case 1:
        sprintf(buffer, "((%d %c %d) %c %d) %c %d\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        // printf("(%d %c %d) %c %d %c %d\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        *count += 1;
        break;
    case 2:
        sprintf(buffer, "(%d %c (%d %c %d)) %c %d\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        // printf("%d %c (%d %c %d) %c %d\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        *count += 1;
        break;
    case 3:
        sprintf(buffer, "(%d %c %d) %c (%d %c %d)\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        *count += 1;
        break;
    case 4:
        sprintf(buffer, "%d %c ((%d %c %d) %c %d)\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        // printf("%d %c (%d %c %d %c %d)\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        *count += 1;
        break;
    case 5:
        sprintf(buffer, "%d %c (%d %c (%d %c %d))\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        // printf("%d %c %d %c (%d %c %d)\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        *count += 1;
        break;
    default:
        break;
    }

    cout << buffer;
    sol->push_back(buffer);
}

float calculate(char op, float num1, float num2)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    default:
        cerr << "Operator tidak valid!" << endl;
        throw -1;
    }
}

void eval(char opvalid[], vector<int> cards, float GOAL, int *count, vector<string> *sol)
{
    int i, j, k;
    float res;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 4; k++)
            {
                char ops[3] = {opvalid[i], opvalid[j], opvalid[k]};

                // pattern 1
                res = calculate(ops[0], cards[0], cards[1]);
                res = calculate(ops[1], res, cards[2]);
                res = calculate(ops[2], res, cards[3]);
                if (res == GOAL)
                {
                    display(cards, ops, 1, count, sol);
                }

                // pattern 2
                res = calculate(ops[1], cards[1], cards[2]);
                res = calculate(ops[0], cards[0], res);
                res = calculate(ops[2], res, cards[3]);
                if (res == GOAL)
                {
                    display(cards, ops, 2, count, sol);
                }

                // pattern 3
                float res1 = calculate(ops[0], cards[0], cards[1]);
                float res2 = calculate(ops[2], cards[2], cards[3]);
                res = calculate(ops[1], res1, res2);
                if (res == GOAL)
                {
                    display(cards, ops, 3, count, sol);
                }

                // pattern 4
                res = calculate(ops[1], cards[1], cards[2]);
                res = calculate(ops[2], res, cards[3]);
                res = calculate(ops[0], cards[0], res);
                if (res == GOAL)
                {
                    display(cards, ops, 4, count, sol);
                }

                // pattern 5
                res = calculate(ops[2], cards[2], cards[3]);
                res = calculate(ops[1], cards[1], res);
                res = calculate(ops[0], cards[0], res);
                if (res == GOAL)
                {
                    display(cards, ops, 5, count, sol);
                }
            }
        }
    }
}

void swap(float &a, float &b)
{
    float temp = a;
    a = b;
    b = temp;
}

bool isSwap(vector<int> nums, int start, int curr)
{
    for (int i = start; i < curr; i++)
    {
        if (nums[i] == nums[curr])
        {
            return 0;
        }
    }
    return 1;
}

void permutation(vector<int> nums, int idx, int n, char opvalid[], int *count, vector<string> *sol)
{
    if (idx >= n)
    {
        eval(opvalid, nums, 24, count, sol);
        return;
    }

    for (int i = idx; i < n; i++)
    {
        bool check = isSwap(nums, idx, i);
        if (check)
        {
            swap(nums[idx], nums[i]);
            permutation(nums, idx + 1, n, opvalid, count, sol);
            swap(nums[idx], nums[i]);
        }
    }
}

int main()
{
    const float GOAL = 24.0;

    string menu, input, save, filename;
    string *result;

    float res;
    // float cards[4];
    int count = 0;

    vector<string> sol;
    vector<int> testing;

    string cardvalid[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    char opvalid[4] = {'+', '-', '*', '/'};

    int i, j, k;

    cout << "24 GAME SOLVER" << endl
         << endl;

    cout << "Pilihan:" << endl;
    cout << "1. Input dari keyboard" << endl;
    cout << "2. Generate dari program" << endl
         << endl;

    // input dan validasi menu
    do
    {
        cout << "Pilih menu (1/2) : ";
        cin >> menu;
    } while (menu != "1" && menu != "2" && printf("Masukan tidak sesuai!\n"));

    // menu sudah pasti benar
    if (menu == "1")
    {
        for (i = 0; i < 4; i++)
        {
            // input dan validasi angka/huruf masukan
            do
            {
                cout << "Masukkan angka/huruf ke-" << i + 1 << ": ";
                cin >> input;
                result = find(begin(cardvalid), end(cardvalid), input);
            } while (result == end(cardvalid) && printf("Masukan tidak sesuai!\n"));

            // cards[i] = distance(cardvalid, result) + 1;
            testing.push_back(distance(cardvalid, result) + 1);
        }
    }
    else // menu == 2
    {
        // menggunakan current time untuk seed random
        srand(time(0));

        // angka yang valid (1-13)
        int N = 13;

        for (i = 0; i < 4; i++)
        {
            // cards[i] = (rand() % N) + 1;
            testing.push_back((rand() % N) + 1);
            cout << cardvalid[testing[i] - 1] << " ";
        }
        cout << endl;
    }

    // start stopwatch
    auto start = chrono::system_clock::now();

    permutation(testing, 0, 4, opvalid, &count, &sol);

    if (count == 0)
    {
        sol.push_back("Tidak ada solusi\n");
        cout << "Tidak ada solusi" << endl;
    }
    else
    {
        cout << "Total terdapat " << count << " solusi" << endl;
    }

    // end stopwatch
    auto end = chrono::system_clock::now();

    // output waktu eksekusi program
    chrono::duration<double> time = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Waktu eksekusi: " << time.count() << " s" << endl
         << endl;

    // save solusi
    do
    {
        cout << "Apakah ingin menyimpan solusi? (y/n) : ";
        cin >> save;
    } while (save != "y" && save != "n" && printf("Masukan tidak sesuai!\n"));

    if (save == "y")
    {
        cout << "Masukkan nama file yang diinginkan beserta formatnya (.txt) : ";
        cin >> filename;
        fstream file;
        file.open("../test/" + filename, ios_base::out);

        for (i = 0; i < sol.size(); i++)
        {
            file << sol[i];
        }

        cout << "Berhasil menyimpan solusi pada " << filename << endl;
    }

    cout << endl
         << "Terima kasih telah menggunakan 24 Game Solver" << endl;

    return 0;
}