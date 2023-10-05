#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <fstream>
using namespace std;

inline bool isTwoDigit(int a) {
    return (10 <= a && a <= 99);
}

inline bool isOneDigit(int a) {
    return (0 <= a && a <= 9);
}

inline bool isThreeDigits(int a) {
    return a >= 100;
}

enum Digits {
    One, Two, Three
};

vector<int> numberRange[3] = { vector<int>(), vector<int>(), vector<int>() };

void init() {
    int j = 0;
    for (int i = 0; i < 1000; i++) {
        if (i == 10 || i == 100) {
            j++;
        }
        numberRange[j].push_back(i);
    }
}

int main() {
    init();
    vector<string> validExpressionString;
    char buf[9] = { 0 };
    // 1 + 2 = 3 & 2 + 1 = 3
    for (int i : numberRange[One]) {
        for (int j : numberRange[Two]) {
            if (isThreeDigits(i + j)) {
                sprintf(buf, "%d+%d=%d", i, j, i + j);
                validExpressionString.push_back(buf);
                sprintf(buf, "%d+%d=%d", j, i, i + j);
                validExpressionString.push_back(buf);
            }
        }
    }
    // 1 * 2 = 3 & 2 * 1 = 3
    for (int i : numberRange[One]) {
        for (int j : numberRange[Two]) {
            if (isThreeDigits(i * j)) {
                sprintf(buf, "%d*%d=%d", i, j, i * j);
                validExpressionString.push_back(buf);
                sprintf(buf, "%d*%d=%d", j, i, i * j);
                validExpressionString.push_back(buf);
            }
        }
    }
    // 3 - 1 = 2
    for (int i : numberRange[Three]) {
        for (int j : numberRange[One]) {
            if (isTwoDigit(i - j)) {
                sprintf(buf, "%d-%d=%d", i, j, i - j);
                validExpressionString.push_back(buf);
            }
        }
    }
    // 3 / 1 = 2
    for (int i : numberRange[Three]) {
        for (int j : numberRange[One]) {
            if (j != 0 && i % j == 0 && isTwoDigit(i / j)) {
                sprintf(buf, "%d/%d=%d", i, j, i / j);
                validExpressionString.push_back(buf);
            }
        }
    }
    // 2 + 2 = 2, not repeated
    for (int i : numberRange[Two]) {
        for (int j : numberRange[Two]) {
            if (isTwoDigit(i + j)) {
                sprintf(buf, "%d+%d=%d", i, j, i + j);
                validExpressionString.push_back(buf);
            }
        }
    }
    // 2 - 2 = 2
    for (int i : numberRange[Two]) {
        for (int j : numberRange[Two]) {
            if (isTwoDigit(i - j)) {
                sprintf(buf, "%d-%d=%d", i, j, i - j);
                validExpressionString.push_back(buf);
            }
        }
    }
    // 1 o 1 o 1 = 2
    for (int i : numberRange[One]) {
        for (int j : numberRange[One]) {
            for (int k : numberRange[One]) {
                if (isTwoDigit(i + j + k)) {
                    sprintf(buf, "%d+%d+%d=%d", i, j, k, i + j + k);
                    validExpressionString.push_back(buf);
                }
                if (isTwoDigit(i + j - k)) {
                    sprintf(buf, "%d+%d-%d=%d", i, j, k, i + j - k);
                    validExpressionString.push_back(buf);
                }
                if (isTwoDigit(i + j * k)) {
                    sprintf(buf, "%d+%d*%d=%d", i, j, k, i + j * k);
                    validExpressionString.push_back(buf);
                }
                if (k != 0 && j % k == 0 && isTwoDigit(i + j / k)) {
                    sprintf(buf, "%d+%d/%d=%d", i, j, k, i + j / k);
                    validExpressionString.push_back(buf);
                }
                if (isTwoDigit(i - j + k)) {
                    sprintf(buf, "%d-%d+%d=%d", i, j, k, i - j + k);
                    validExpressionString.push_back(buf);
                }
                // 1 - 1 - 1 < 2
                // 1 - 1 * 1 < 2
                // 1 - 1 / 1 < 2
                if (isTwoDigit(i * j + k)) {
                    sprintf(buf, "%d*%d+%d=%d", i, j, k, i * j + k);
                    validExpressionString.push_back(buf);
                }
                if (isTwoDigit(i * j - k)) {
                    sprintf(buf, "%d*%d-%d=%d", i, j, k, i * j - k);
                    validExpressionString.push_back(buf);
                }
                if (isTwoDigit(i * j * k)) {
                    sprintf(buf, "%d*%d*%d=%d", i, j, k, i * j * k);
                    validExpressionString.push_back(buf);
                }
                if (k != 0 && i * j % k == 0 && isTwoDigit(i * j / k)) {
                    sprintf(buf, "%d*%d/%d=%d", i, j, k, i * j / k);
                    validExpressionString.push_back(buf);
                }
                if (j != 0 && i % j == 0 && isTwoDigit(i / j + k)) {
                    sprintf(buf, "%d/%d+%d=%d", i, j, k, i / j + k);
                    validExpressionString.push_back(buf);
                }
                // 1 / 1 - 1 < 2
                if (j != 0 && i * k % j == 0 && isTwoDigit(i * k / j)) {
                    sprintf(buf, "%d/%d*%d=%d", i, j, k, i * k / j);
                    validExpressionString.push_back(buf);
                }
                // 1 / 1 / 1  < 2
            }
        }
    }
    // 3 - 2 = 1
    for (int i : numberRange[Three]) {
        for (int j : numberRange[Two]) {
            if (isOneDigit(i - j)) {
                sprintf(buf, "%d-%d=%d", i, j, i - j);
                validExpressionString.push_back(buf);
            }
        }
    }
    // 3 / 2 = 1
    for (int i : numberRange[Three]) {
        for (int j : numberRange[Two]) {
            if (j != 0 && i % j == 0 && isOneDigit(i / j)) {
                sprintf(buf, "%d/%d=%d", i, j, i / j);
                validExpressionString.push_back(buf);
            }
        }
    }
    // 1 o 1 o 2 = 1
    for (int i: numberRange[One]) {
        for (int j : numberRange[One]) {
            for (int k : numberRange[Two]) {
                // 1 + 1 + 2 > 1
                // 1 + 1 - 2
                if (isOneDigit(i + j - k)) {
                    sprintf(buf, "%d+%d-%d=%d", i, j, k, i + j - k);
                    validExpressionString.push_back(buf);
                }
                // 1 + 1 * 2 > 1
                // 1 + 1 / 2: not valid
                // 1 - 1 + 2
                if (isOneDigit(i - j + k)) {
                    sprintf(buf, "%d-%d+%d=%d", i, j, k, i - j + k);
                    validExpressionString.push_back(buf);
                }
                // 1 - 1 * 2 < 1
                // 1 - 1 / 2: not valid
                // 1 * 1 + 2 > 1
                // 1 * 1 - 2
                if (isOneDigit(i * j - k)) {
                    sprintf(buf, "%d*%d-%d=%d", i, j, k, i * j - k);
                    validExpressionString.push_back(buf);
                }
                // 1 * 1 * 2 > 1
                // 1 * 1 / 2
                if (k != 0 && i * j % k == 0 && isOneDigit(i * j / k)) {
                    sprintf(buf, "%d*%d/%d=%d", i, j, k, i * j / k);
                    validExpressionString.push_back(buf);
                }
                // 1 / 1 + 2 > 1
                // 1 / 1 - 2 < 1
                // 1 / 1 * 2
                if (j != 0 && i * k % j == 0 && isOneDigit(i * k / j)) {
                    sprintf(buf, "%d/%d*%d=%d", i, j, k, i * k / j);
                    validExpressionString.push_back(buf);
                }
                // 1 / 1 / 2: not valid
            }
        }
    }
    // 1 o 2 o 1 = 1
    for (int i: numberRange[One]) {
        for (int j : numberRange[Two]) {
            for (int k : numberRange[One]) {
                // 1 + 2 + 1 > 1
                // 1 + 2 - 1
                if (isOneDigit(i + j - k)) {
                    sprintf(buf, "%d+%d-%d=%d", i, j, k, i + j - k);
                    validExpressionString.push_back(buf);
                }
                // 1 + 2 * 1 > 1
                // 1 + 2 / 1
                if (k != 0 && j % k == 0 && isOneDigit(i + j / k)) {
                    sprintf(buf, "%d+%d/%d=%d", i, j, k, i + j / k);
                    validExpressionString.push_back(buf);
                }
                // 1 - 2 + 1
                if (isOneDigit(i - j + k)) {
                    sprintf(buf, "%d-%d+%d=%d", i, j, k, i - j + k);
                    validExpressionString.push_back(buf);
                }
                // 1 - 2 - 1 < 1
                // 1 - 2 * 1 < 1
                // 1 - 2 / 1
                if (k != 0 && j % k == 0 && isOneDigit(i - j / k)) {
                    sprintf(buf, "%d-%d/%d=%d", i, j, k, i - j / k);
                    validExpressionString.push_back(buf);
                }
                // 1 * 2 + 1 > 1
                // 1 * 2 - 1
                if (isOneDigit(i * j - k)) {
                    sprintf(buf, "%d*%d-%d=%d", i, j, k, i * j - k);
                    validExpressionString.push_back(buf);
                }
                // 1 * 2 * 1 > 1
                // 1 * 2 / 1
                if (k != 0 && i * j % k == 0 && isOneDigit(i * j / k)) {
                    sprintf(buf, "%d*%d/%d=%d", i, j, k, i * j / k);
                    validExpressionString.push_back(buf);
                }
                // 1 / 2 + 1 not valid
                // 1 / 2 - 1 not valid
                // 1 / 2 * 1
                if (j != 0 && i * k % j == 0 && isOneDigit(i * k / j)) {
                    sprintf(buf, "%d/%d*%d=%d", i, j, k, i * k / j);
                    validExpressionString.push_back(buf);
                }
                // 1 / 2 / 1: not valid
            }
        }
    }
    // 2 o 1 o 1 = 1
    for (int i: numberRange[Two]) {
        for (int j : numberRange[One]) {
            for (int k : numberRange[One]) {
                // 2 + 1 + 1 > 1
                // 2 + 1 - 1
                if (isOneDigit(i + j - k)) {
                    sprintf(buf, "%d+%d-%d=%d", i, j, k, i + j - k);
                    validExpressionString.push_back(buf);
                }
                // 2 + 1 * 1 > 1
                // 2 + 1 / 1 > 1
                // 2 - 1 + 1
                if (isOneDigit(i - j + k)) {
                    sprintf(buf, "%d-%d+%d=%d", i, j, k, i - j + k);
                    validExpressionString.push_back(buf);
                }
                // 2 - 1 - 1
                if (isOneDigit(i - j - k)) {
                    sprintf(buf, "%d-%d-%d=%d", i, j, k, i - j - k);
                    validExpressionString.push_back(buf);
                }
                // 2 - 1 * 1 
                if (isOneDigit(i - j * k)) {
                    sprintf(buf, "%d-%d*%d=%d", i, j, k, i - j * k);
                    validExpressionString.push_back(buf);
                }
                // 2 - 1 / 1
                if (k != 0 && j % k == 0 && isOneDigit(i - j / k)) {
                    sprintf(buf, "%d-%d/%d=%d", i, j, k, i - j / k);
                    validExpressionString.push_back(buf);
                }
                // 2 * 1 + 1 > 1
                // 2 * 1 - 1
                if (isOneDigit(i * j - k)) {
                    sprintf(buf, "%d*%d-%d=%d", i, j, k, i * j - k);
                    validExpressionString.push_back(buf);
                }
                // 2 * 1 * 1 > 1
                // 2 * 1 / 1
                if (k != 0 && i * j % k == 0 && isOneDigit(i * j / k)) {
                    sprintf(buf, "%d*%d/%d=%d", i, j, k, i * j / k);
                    validExpressionString.push_back(buf);
                }
                // 2 / 1 + 1 
                if (j != 0 && i % j == 0 && isOneDigit(i / j + k)) {
                    sprintf(buf, "%d/%d+%d=%d", i, j, k, i / j + k);
                    validExpressionString.push_back(buf);
                }
                // 2 / 1 - 1
                if (j != 0 && i % j == 0 && isOneDigit(i / j - k)) {
                    sprintf(buf, "%d/%d-%d=%d", i, j, k, i / j - k);
                    validExpressionString.push_back(buf);
                }
                // 2 / 1 * 1
                if (j != 0 && i * k % j == 0 && isOneDigit(i * k / j)) {
                    sprintf(buf, "%d/%d*%d=%d", i, j, k, i * k / j);
                    validExpressionString.push_back(buf);
                }
                // 2 / 1 / 1
                if (j != 0 && k != 0 && i % (j * k) == 0 && isOneDigit(i / j / k)) {
                    sprintf(buf, "%d/%d/%d=%d", i, j, k, i / j / k);
                    validExpressionString.push_back(buf);
                }
            }
        }
    }
    sort(validExpressionString.begin(), validExpressionString.end());
    ofstream fout("valid_expressions.txt");
    for (auto s : validExpressionString) {
        fout << s << endl;
    }
    return 0;
}
