//
// Created by Branden Frieden on 1/18/23.
//
#include <iostream>
#include <string>
#include "expr.h"


////////// NumExpr
NumExpr::NumExpr(int val) {
    this->val = val;
}

bool NumExpr::equals(Expr *e){
    NumExpr *n = dynamic_cast<NumExpr*>(e);
    if (n == nullptr)
        return false;
    else
        return (this->val == n->val);
}

int NumExpr::interp(){
    return val;
}

bool NumExpr::has_variable(){
    return false;
}

Expr* NumExpr::subst(std::string variable, Expr* e){
    return new NumExpr(val);
}


//////////// AddExpr
AddExpr::AddExpr(Expr *lhs, Expr *rhs) {
this->lhs = lhs;
this->rhs = rhs;
}

bool AddExpr::equals(Expr *e) {
    AddExpr *a = dynamic_cast<AddExpr *>(e);
    if (a == nullptr)
        return false;
    else
        return (this->lhs->equals(a->lhs) &&
                this->rhs->equals(a->rhs));
}

int AddExpr::interp(){
    return (this->lhs->interp() + this->rhs->interp());
}

bool AddExpr::has_variable(){
    return (lhs->has_variable() || rhs->has_variable());
}

Expr* AddExpr::subst(std::string variable, Expr* e){
    return (new AddExpr(this->lhs->subst(variable, e), this->rhs->subst(variable, e)));
}

//////////// MultExpr
MultExpr::MultExpr(Expr *lhs, Expr *rhs) {
this->lhs = lhs;
this->rhs = rhs;
}

bool MultExpr::equals(Expr *e) {
    MultExpr *m = dynamic_cast<MultExpr *>(e);
    if (m == nullptr)
        return false;
    else
        return (this->lhs->equals(m->lhs) &&
                this->rhs->equals(m->rhs));
}

int MultExpr::interp(){
    return (this->lhs->interp() * this->rhs->interp());
}

bool MultExpr::has_variable(){
    return (lhs->has_variable() || rhs->has_variable());
}

Expr* MultExpr::subst(std::string variable, Expr* e){
    return (new MultExpr(this->lhs->subst(variable, e), this->rhs->subst(variable, e)));
}

//////////// VarExpr

VarExpr::VarExpr(std::string variable) {
this->var = variable;
}

bool VarExpr::equals(Expr *e){
    VarExpr *n = dynamic_cast<VarExpr*>(e);
    if (n == nullptr)
        return false;
    else
        return (this->var == n->var);
}

int VarExpr::interp(){
    throw std::runtime_error("VarExpr has no interpretable value");
}

bool VarExpr::has_variable(){
    return true;
}

Expr* VarExpr::subst(std::string variable, Expr* e){
    if(this->var == variable){
        return e;
    }
    else
        return new VarExpr(var);
}
