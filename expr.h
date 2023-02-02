//
// Created by Branden Frieden on 1/18/23.
//

#ifndef HW02_EXPRESSION_EXPR_H
#define HW02_EXPRESSION_EXPR_H

#include <iostream>
#include <string>


class Expr {
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(std::string, Expr*) = 0;
};

class NumExpr : public Expr {
public:
    int val;
    NumExpr(int val);
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(std::string, Expr*);
};

class AddExpr : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    AddExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(std::string, Expr*);
};

class MultExpr : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    MultExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(std::string, Expr*);
};

class VarExpr : public Expr {
public:
    std::string var;
    VarExpr(std::string variable);
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(std::string, Expr*);
};


#endif //HW02_EXPRESSION_EXPR_H
