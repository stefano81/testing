#pragma once

class Expression {
public:
  virtual ~Expression() {}

  virtual Expression *clone() = 0;

  virtual int value() = 0;
};

class Plus : public Expression {
  Expression *mleft, *mright;

public:
  Plus(Expression *left, Expression *right) : mleft{left}, mright{right} {}
  Plus(const Plus &other) {
    mleft = other.mleft->clone();
    mright = other.mright->clone();
  }
  Plus & operator=(const Plus &other) {
    if (&other != this) {
      delete mleft;
      delete mright;

      mleft = other.mleft->clone();
      mright = other.mright->clone();
    }
  }

  virtual ~Plus() override {
    delete mleft;
    delete mright;
  }
  virtual Expression *clone() override {
    return new Plus(*this);
  }
  virtual int value() override {
    return mleft->value() + mright->value();
  }
};

class Times : public Expression {
  Expression *mleft, *mright;

public:
  Times(Expression *left, Expression *right) : mleft{left}, mright{right} {}
  Times(const Times &other) {
    mleft = other.mleft->clone();
    mright = other.mright->clone();
  }
  Times & operator=(const Times &other) {
    if (&other != this) {
      delete mleft;
      delete mright;

      mleft = other.mleft->clone();
      mright = other.mright->clone();
    }
  }

  virtual ~Times() override {
    delete mleft;
    delete mright;
  }
  virtual Expression *clone() override {
    return new Times(*this);
  }
  virtual int value() override {
    return mleft->value() * mright->value();
  }
};

class Number : public Expression {
  int mval;

public:
  Number(int val) : mval{val} {}
  Number(const Number &other) : mval{other.mval} {}

  Number & operator=(const Number &other) {
    if (&other != this) {
      mval = other.mval;
    }
  }

  virtual Expression *clone() override {
    return new Number(*this);
  }
  virtual int value() override {
    return mval;
  }
};

class Ident : public Expression {
  int *mval;

public:
  Ident(int *val) : mval{val} {}
  Ident(const Ident &other) : mval{other.mval} {}

  Ident & operator=(const Ident &other) {
    if (&other != this) {
      mval = other.mval;
    }
  }

  virtual Expression *clone() override {
    return new Ident(*this);
  }
  virtual int value() override {
    return *mval;
  }
};
