
// Subhan Ali
// Farwa Iqbal
// Amna Nasir

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

// ============================================================
// CONSTANTS - Pakki values (kabhi nahi badalti)
// ============================================================
const double PI = 3.14159265358979323846;
const double E = 2.71828182845904523536;

// ============================================================
// FUNCTION PROTOTYPES - Aage batana ke ye functions hain
// ============================================================
double jumla(string s, int &p);
double zarab_taqseem(string s, int &p);
double quwwat(string s, int &p);
double adad(string s, int &p);
double bunyadi(string s, int &p);
void spacesHatao(string s, int &p);
void menuDikhao();

// ============================================================
// FUNCTION 1: spacesHatao - Khali jaga (space) ko ignore karo
// ============================================================
void spacesHatao(string s, int &p) {
  while (p < s.length() && s[p] == ' ') {
    p++;
  }
}

// ============================================================
// FUNCTION 2: adad - String se number (integer/float) banao
// ============================================================
double adad(string s, int &p) {
  double num = 0;
  double decimal = 0.1;
  bool point = false;

  while (p < s.length()) {
    char ch = s[p];
    if (ch >= '0' && ch <= '9') {
      if (point == false) {
        num = num * 10 + (ch - '0');
      } else {
        num = num + (ch - '0') * decimal;
        decimal = decimal / 10;
      }
      p++;
    } else if (ch == '.') {
      point = true;
      p++;
    } else {
      break;
    }
  }
  return num;
}

// ============================================================
// FUNCTION 3: bunyadi  Base elements (numbers, brackets, functions)
// Yeh sab se neechay wala function hai (base level)
// ============================================================
double bunyadi(string s, int &p) {
  spacesHatao(s, p);

  // Agar expression khatam ho gayi toh error
  if (p >= s.length()) {
    cout << "Error: Ghalat expression hai!" << endl;
    return 0;
  }

  // Unary Plus (+5)
  if (s[p] == '+') {
    p++;
    return bunyadi(s, p);
  }

  // Unary Minus (-5)
  if (s[p] == '-') {
    p++;
    return -bunyadi(s, p);
  }

  // Brackets ( (2+3) )
  if (s[p] == '(') {
    p++;
    double jawab = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return jawab;
  }

  // ==========================================
  // 4-LETTER FUNCTIONS (Pehle check karo)
  // ==========================================

  // 1. SINH - Hyperbolic sine
  if (s.substr(p, 4) == "sinh") {
    p = p + 4;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return sinh(x);
  }

  // 2. COSH - Hyperbolic cosine
  if (s.substr(p, 4) == "cosh") {
    p = p + 4;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return cosh(x);
  }

  // 3. TANH - Hyperbolic tangent
  if (s.substr(p, 4) == "tanh") {
    p = p + 4;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return tanh(x);
  }

  // 4. SQRT - Square root (mool jazar)
  if (s.substr(p, 4) == "sqrt") {
    p = p + 4;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return sqrt(x);
  }

  // 5. CBRT - Cube root (teen wala jazar)
  if (s.substr(p, 4) == "cbrt") {
    p = p + 4;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return cbrt(x);
  }

  // 6. ASIN - Arc sine (degree mein jawab)
  if (s.substr(p, 4) == "asin") {
    p = p + 4;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return asin(x) * 180 / PI;
  }

  // 7. ACOS - Arc cosine
  if (s.substr(p, 4) == "acos") {
    p = p + 4;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return acos(x) * 180 / PI;
  }

  // 8. ATAN - Arc tangent
  if (s.substr(p, 4) == "atan") {
    p = p + 4;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return atan(x) * 180 / PI;
  }

  // 9. FACT - Factorial (5! = 120)
  if (s.substr(p, 4) == "fact") {
    p = p + 4;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    double result = 1;
    for (int i = 1; i <= x; i++) {
      result = result * i;
    }
    return result;
  }

  // ==========================================
  // 3-LETTER FUNCTIONS
  // ==========================================

  // 10. SIN - Sine (degree mein input)
  if (s.substr(p, 3) == "sin") {
    p = p + 3;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return sin(x * PI / 180);
  }

  // 11. COS - Cosine (degree mein input)
  if (s.substr(p, 3) == "cos") {
    p = p + 3;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return cos(x * PI / 180);
  }

  // 12. TAN - Tangent (degree mein input)
  if (s.substr(p, 3) == "tan") {
    p = p + 3;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return tan(x * PI / 180);
  }

  // 13. LOG - Log base 10 (aam log)
  if (s.substr(p, 3) == "log") {
    p = p + 3;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return log10(x);
  }

  // 14. EXP - Exponential (e^x)
  if (s.substr(p, 3) == "exp") {
    p = p + 3;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return exp(x);
  }

  // 15. ABS - Absolute value (module)
  if (s.substr(p, 3) == "abs") {
    p = p + 3;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return fabs(x);
  }

  // 16. DEG - Degree ko radian mein badlo
  if (s.substr(p, 3) == "deg") {
    p = p + 3;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return x * PI / 180;
  }

  // 17. RAD - Radian ko degree mein badlo
  if (s.substr(p, 3) == "rad") {
    p = p + 3;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return x * 180 / PI;
  }

  // ==========================================
  // 2-LETTER FUNCTIONS & CONSTANTS
  // ==========================================

  // 18. LN - Natural log (base e)
  if (s.substr(p, 2) == "ln") {
    p = p + 2;
    spacesHatao(s, p);
    if (s[p] == '(')
      p++;
    double x = jumla(s, p);
    spacesHatao(s, p);
    if (s[p] == ')') {
      p++;
    } else {
      cout << "Error: Bracket band nahi kiya ')'" << endl;
      return 0;
    }
    return log(x);
  }

  // 19. PI constant (chhota ya bara pi)
  string lowerPi = s.substr(p, 2);
  if (lowerPi == "pi" || lowerPi == "PI") {
    p = p + 2;
    return PI;
  }

  // 20. E constant (lekin 'exp' nahi hona chahiye)
  string eCheck = s.substr(p, 3);
  if ((s[p] == 'e' || s[p] == 'E') && eCheck != "exp" && eCheck != "EXP") {
    p = p + 1;
    return E;
  }

  // Normal number (aam adad)
  return adad(s, p);
}

// ============================================================
// FUNCTION 4: quwwat - ^ operator (Right-Associative)
// ============================================================
double quwwat(string s, int &p) {
  double jawab = bunyadi(s, p);
  spacesHatao(s, p);

  if (p < s.length() && s[p] == '^') {
    p++;
    double second = quwwat(s, p);
    jawab = pow(jawab, second);
  }

  return jawab;
}

// ============================================================
// FUNCTION 5: zarab_taqseem - *, /, % operators
// ============================================================
double zarab_taqseem(string s, int &p) {
  double jawab = quwwat(s, p);

  while (p < s.length()) {
    spacesHatao(s, p);

    if (s[p] == '*') {
      p++;
      jawab = jawab * quwwat(s, p);
    } else if (s[p] == '/') {
      p++;
      double second = quwwat(s, p);
      if (second != 0) {
        jawab = jawab / second;
      } else {
        cout << "Error: Zero se divide nahi kar sakte!" << endl;
        return 0;
      }
    } else if (s[p] == '%') {
      p++;
      double second = quwwat(s, p);
      if (second != 0) {
        jawab = fmod(jawab, second);
      } else {
        cout << "Error: Zero se modulo nahi kar sakte!" << endl;
        return 0;
      }
    } else {
      break;
    }
  }

  return jawab;
}

// ============================================================
// FUNCTION 6: jumla - +, - operators
// ============================================================
double jumla(string s, int &p) {
  spacesHatao(s, p);

  if (p >= s.length()) {
    cout << "Error: Khali expression hai!" << endl;
    return 0;
  }

  double jawab = zarab_taqseem(s, p);

  while (p < s.length()) {
    spacesHatao(s, p);

    if (s[p] == '+') {
      p++;
      jawab = jawab + zarab_taqseem(s, p);
    } else if (s[p] == '-') {
      p++;
      jawab = jawab - zarab_taqseem(s, p);
    } else {
      break;
    }
  }

  return jawab;
}

// ============================================================
// FUNCTION 7: menuDikhao - User ko menu dikhana
// ============================================================
void menuDikhao() {
  cout << "============================================================"
       << endl;
  cout << "              SCIENTIFIC CALCULATOR" << endl;
  cout << "============================================================"
       << endl;
  cout << endl;
  cout << "SUPPORTED FUNCTIONS (Support honay wale functions):" << endl;
  cout << "------------------------------------------------------------"
       << endl;
  cout << "  sin(x)  cos(x)  tan(x)  sqrt(x)  cbrt(x)" << endl;
  cout << "  log(x)  ln(x)   exp(x)  abs(x)   fact(x)" << endl;
  cout << "  asin(x) acos(x) atan(x) sinh(x)  cosh(x)" << endl;
  cout << "  tanh(x) deg(x)  rad(x)  pi       e" << endl;
  cout << "------------------------------------------------------------"
       << endl;
  cout << "OPERATORS (Amal karne wale nishan):" << endl;
  cout << "  +  -  *  /  %  ^  (  )" << endl;
  cout << "------------------------------------------------------------"
       << endl;
  cout << "EXAMPLES (Misaal):" << endl;
  cout << "  2 + 3 * 4" << endl;
  cout << "  (2 + 3) ^ 2" << endl;
  cout << "  sin(30) + cos(60)" << endl;
  cout << "  sqrt(25) + log(100)" << endl;
  cout << "  fact(5) + exp(2)" << endl;
  cout << "  pi * 2" << endl;
  cout << "============================================================"
       << endl;
  cout << endl;
  cout << "Type 'exit' to close the calculator" << endl;
  cout << "============================================================"
       << endl;
  cout << endl;
}

// ============================================================
// MAIN FUNCTION - Program yahan se shuru hota hai
// ============================================================
int main() {
  string input;
  menuDikhao();

  while (true) {
    cout << "Expression likho (aur Enter press karo): ";
    getline(cin, input);

    if (input == "exit" || input == "EXIT") {
      cout << "============================================================"
           << endl;
      cout << "              CALCULATOR BAND KAR DIYA" << endl;
      cout << "============================================================"
           << endl;
      break;
    }

    if (input == " ") {
      continue;
    }

    int position = 0;
    double jawab = jumla(input, position);

    spacesHatao(input, position);

    if (position != input.length()) {
      cout << "Error: Ghalat expression hai!" << endl;
      cout << "------------------------------------------------------------"
           << endl;
      cout << endl;
      continue;
    }

    cout << "------------------------------------------------------------"
         << endl;
    cout << "  " << input << " = ";

    cout << "------------------------------------------------------------"
         << endl;
    cout << "  " << input << " = ";

    if (jawab == (int)jawab) {
      cout << (int)jawab << endl;
    } else {
      cout << fixed << setprecision(6) << jawab << endl;
    }
    cout << "------------------------------------------------------------"
         << endl;
    cout << endl;
  }

  return 0;
}