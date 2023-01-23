#include <bits/stdc++.h>
using namespace std;

// menyimpan solusi yang ditemukan ke dalam variabel sol
void save(vector<int> cards, char ops[], int pattern, int *count, vector<string> *sol)
{
    char buffer[25]; // tempat penyimpanan string solusi sementara

    switch (pattern)
    {
    case 1:
        sprintf(buffer, "((%d %c %d) %c %d) %c %d\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        break;
    case 2:
        sprintf(buffer, "(%d %c (%d %c %d)) %c %d\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        break;
    case 3:
        sprintf(buffer, "(%d %c %d) %c (%d %c %d)\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        break;
    case 4:
        sprintf(buffer, "%d %c ((%d %c %d) %c %d)\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        break;
    case 5:
        sprintf(buffer, "%d %c (%d %c (%d %c %d))\n", cards[0], ops[0], cards[1], ops[1], cards[2], ops[2], cards[3]);
        break;
    default:
        cerr << "Pola tidak valid!" << endl;
        throw -1;
    }

    *count += 1;            // banyaknya solusi ditambah 1
    sol->push_back(buffer); // menyimpan string solusi
}

// mengembalikan hasil operasi sesuai operator
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

// melakukan brute force terhadap operator yang valid dan kelima pola
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
                    save(cards, ops, 1, count, sol);
                }

                // pattern 2
                res = calculate(ops[1], cards[1], cards[2]);
                res = calculate(ops[0], cards[0], res);
                res = calculate(ops[2], res, cards[3]);
                if (res == GOAL)
                {
                    save(cards, ops, 2, count, sol);
                }

                // pattern 3
                float res1 = calculate(ops[0], cards[0], cards[1]);
                float res2 = calculate(ops[2], cards[2], cards[3]);
                res = calculate(ops[1], res1, res2);
                if (res == GOAL)
                {
                    save(cards, ops, 3, count, sol);
                }

                // pattern 4
                res = calculate(ops[1], cards[1], cards[2]);
                res = calculate(ops[2], res, cards[3]);
                res = calculate(ops[0], cards[0], res);
                if (res == GOAL)
                {
                    save(cards, ops, 4, count, sol);
                }

                // pattern 5
                res = calculate(ops[2], cards[2], cards[3]);
                res = calculate(ops[1], cards[1], res);
                res = calculate(ops[0], cards[0], res);
                if (res == GOAL)
                {
                    save(cards, ops, 5, count, sol);
                }
            }
        }
    }
}

// menukar variabel
void swap(float &a, float &b)
{
    float temp = a;
    a = b;
    b = temp;
}

// mengecek apakah suatu angka perlu ditukar atau tidak (menangani kasus jika ada masukan angka yang ganda)
// jika angka sama (ganda), maka mengembalikan 0 (false) -> tidak perlu ditukar
// jika tidak, maka mengembalikan 1 (true)
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

// melakukan permutasi terhadap angka masukan, serta memanggil fungsi eval (untuk brute force) pada setiap permutasi yang ada
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
    const float GOAL = 24.0; // hasil yang diinginkan

    string menu, input, save, filename, *result; // variabel untuk input

    int count = 0; // banyaknya solusi

    vector<string> sol; // vector penyimpanan solusi
    vector<int> cards;  // vector penyimpanan angka/kartu masukan

    string cardvalid[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}; // array kartu yang valid
    char opvalid[4] = {'+', '-', '*', '/'};                                                    // array operator yang valid

    int i; // variabel untuk iterasi

    cout << "SELAMAT DATANG DI \"24 CARD GAME\" SOLVER" << endl
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

    cout << endl;

    // menu sudah pasti benar

    if (menu == "1") // input dari keyboard
    {
        for (i = 0; i < 4; i++)
        {
            // input dan validasi kartu
            do
            {
                cout << "Masukkan kartu ke-" << i + 1 << ": ";
                cin >> input;
                result = find(begin(cardvalid), end(cardvalid), input);
            } while (result == end(cardvalid) && printf("Masukan tidak sesuai!\n"));

            cards.push_back(distance(cardvalid, result) + 1);
        }
        cout << endl;
    }
    else // menu == 2 -> random
    {
        // menggunakan current time untuk seed random
        srand(time(0));

        // angka yang valid (1-13)
        int N = 13;

        for (i = 0; i < 4; i++)
        {
            cards.push_back((rand() % N) + 1);
        }
    }

    // output susunan kartu masukan
    cout << "Susunan kartu:" << endl;
    for (auto x : cards)
    {
        cout << cardvalid[x - 1] << " ";
    }

    cout << endl
         << endl;

    // start stopwatch
    auto start = chrono::high_resolution_clock::now();

    // proses bruteforce
    permutation(cards, 0, 4, opvalid, &count, &sol);

    // end stopwatch
    auto end = chrono::high_resolution_clock::now();

    // output solusi
    if (count == 0)
    {
        sol.push_back("Tidak ada solusi yang ditemukan\n");
        cout << sol[0];
    }
    else
    {
        cout << "Terdapat " << count << " solusi yang ditemukan:" << endl;

        for (auto x : sol)
        {
            cout << x;
        }
    }

    // output waktu eksekusi program
    auto time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << endl
         << "Waktu eksekusi: " << time.count() << " mikrosekon" << endl
         << endl;

    // menyimpan solusi ke file txt
    do
    {
        cout << "Apakah ingin menyimpan solusi? (y/n) : ";
        cin >> save;
    } while (save != "y" && save != "n" && printf("Masukan tidak sesuai!\n"));

    if (save == "y")
    {
        cout << endl
             << "Masukkan nama file yang diinginkan : ";
        cin >> filename;
        fstream file;
        file.open("test/" + filename + ".txt", ios_base::out);

        for (i = 0; i < sol.size(); i++)
        {
            file << sol[i];
        }

        cout << "Berhasil menyimpan solusi pada test/" << filename << ".txt" << endl;
    }

    cout << endl
         << "Terima kasih telah menggunakan \"24 Card Game\" Solver" << endl;

    return 0;
}