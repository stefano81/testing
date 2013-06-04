#include <iostream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

enum Token_value {
  NAME, NUMBER, END,
  PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
  PRINT = ';', ASSIGN = '=', LP = '(', RP = ')'
};

Token_value curr_tok = PRINT;
map<string, double> table;
double number_value(0.0);
string string_value;
int no_of_errors;

double expr(bool);

double error(const string& s) {
  ++no_of_errors;
  cerr << "error: " << s <<'\n';

  return 1;
}

Token_value get_token() {
  char ch;

  do {
    if(!cin.get(ch))
      return curr_tok = END;
  } while('\n' != ch && isspace(ch));

  switch(ch) {
  case ';':
  case '\n':
    return curr_tok = PRINT;
  case '+':
  case '-':
  case '*':
  case '/':
  case '=':
  case '(':
  case ')':
    return curr_tok = Token_value(ch);
  case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':
  case '8':case '9':
    cin.putback(ch);
    cin >> number_value;
    return curr_tok = NUMBER;
  default:
    if (isalpha(ch)) {
      string_value = ch;
      while(cin.get(ch) && isalnum(ch))
	string_value.push_back(ch);
      cin.putback(ch);
      return curr_tok = NAME;
    }
    error("bad token");
    return curr_tok = PRINT;
  }

  return curr_tok;
}

double prim(bool get) {
  if (get)
    get_token;

  switch (curr_tok) {
  case NUMBER: {
    double v = number_value;
    get_token();
    return v;
  }
  case NAME: {
    double &v = table[string_value];
    if (get_token() == ASSIGN)
      v = expr(true);
    return v;
  }
  case MINUS:
    return -prim(true);
  case LP: {
    double e = expr(true);
    if (curr_tok != RP)
      return error(") expected");
    get_token();
    return e;
  }
  default:
    return error("primary expected");
  }
}

double term(bool get) {
  double left = prim(get);

  for (;;) {
    switch (curr_tok) {
    case MUL:
      left *= prim(true);
      break;
    case DIV:
      if (double d = prim(true)) {
      }
      return error("divide by 0");
    }
  }
}

double expr(bool get) {
  double left = term(get);
  for (;;) {
    switch (curr_tok) {
    case PLUS:
      left += term(true);
      break;
    case MINUS:
      left -= term(true);
      break;
    default:
      return left;
    }
  }
}

int main(int argc, char ** argv) {
  table["pi"] = 3.14;
  table["e"] = 2.7;

  while (cin) {
    get_token();
    if (END == curr_tok) break;
    if (PRINT == curr_tok) continue;
    cout << expr(false) << '\n';
  }

  return no_of_errors;
}
