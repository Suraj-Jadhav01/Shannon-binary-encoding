#include <iostream>
#include <math.h>
#include <string.h>
#include <cmath>

using namespace std;
int main()
{
    int num;
    
    cout << "enter the number of symbols ";
    cin >> num;
    float prob[num];
    cout << "enter probability of symbols :" << endl;
    for (int i = 0; i < num; i++)
    {
        cout << "probability of symbol " << i << " :";
        cin >> prob[i];
        if (prob[i] > 1)
        {
            cout << "ERROR: probality must be less than 1" << endl;
            cout << "probability of symbol " << i << " :";
            cin >> prob[i];
        }
    }

    // step1:To arrange probability in descending order

    float temp;
    int i, k, j;
    for (i = 0; i < num; i++)
    {
        for (j = i; j < num; j++)
        {
            if (prob[j] > prob[i])
            {
                temp = prob[i];
                prob[i] = prob[j];
                prob[j] = temp;
            }
        }
    }

    // step2:to find alpha values
    
    float alp[num + 1];
    alp[0] = 0;
    for (i = 1; i <= num; i++)
    {
        alp[i] = alp[i - 1] + prob[i - 1];
    }

    // step 3
    
    int li[num];
    for (int i = 0; i < num; i++)
    {
        li[i] = 0;
        for (j = 0; j < 10; j++)
        {
            if (pow(2, j) >= (1 / prob[i]))
            {
                li[i] = j;
                break;
            }
        }
    }

    // step 4:
    
    float a, b_prob[num];
    for (i = 0; i < num; i++)
    {
        a = alp[i];
        b_prob[i] = 0;
        for (j = 1; j < 10; j++)
        {
            a *= 2;
            if (a == 1)
            {
                b_prob[i] += pow(.1, j);
                break;
            }
            else if (a > 1)
            {
                a--;
                b_prob[i] += pow(.1, j);
            }
        }
    }
    // step5
    char cord_word[num][10] = {""};
    float b;
    for (i = 0; i < num; i++)
    {
        a = li[i];
        b = b_prob[i];
        for (k = 0; k < a; k++)
        {
            b = b * 10;
            if (b >= 1)
            {
                b--;
                strcat(cord_word[i], "1");
            }
            else if (b < 1)
            {
                strcat(cord_word[i], "0");
            }
        }
    }
    // efficency of codewords
    float hs = 0, l = 0, eff, rdn;
    for (i = 0; i < num; i++)
    {
        hs += prob[i] * log2(1 / prob[i]);
        l += prob[i] * li[i];
    }
    eff = (hs / l) * 100;
    rdn = 100 - eff;

    // display
    for (int i = 0; i < num; i++)
    {
        cout << "\nprobability of symbol s[" << i << "] :" << prob[i];
        cout << "\talph [" << i << "] :" << alp[i];
        cout << "\tli[" << i << "] :" << li[i];
        cout << "\tbinary form probality " << b_prob[i];
    }
    cout << "\nalph [" << num << "] :";
    cout << alp[num] << endl;

    for (int i = 0; i < num; i++)
    {
        cout << "code words are " << cord_word[i] << endl;
    }
    cout << "H(s)=" << hs << "\nL=" << l << endl;
    cout << "efficiency of code words is : " << eff << "%" << endl;
    cout << "redundancy of code words is : " << rdn <<"%"<<endl;
}