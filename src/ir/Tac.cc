/*!
 * \file Tac.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "semantic/Symbol.h"
#include "ir/Tac.h"

using namespace std;

int Label::labelCount = 0;
int Temp::tempCount = 0;
map<int, Temp*> *Temp::constTempPool = new map<int , Temp*>();

Label::Label(void) {
}

Label::Label(int id, string name, bool target) {
    this->id = id;

    this->name = name;
    this->target = target;
}

Label *Label::createLabel(void) {
    return createLabel(false);
}

Label *Label::createLabel(bool target) {
    int id = (Label::labelCount)++;
    return new Label(id, "_L" + id, target);
}

Label *Label::createLabel(string name, bool target) {
    int id = (Label::labelCount)++;
    return new Label(id, name, target);
}

string Label::toString(void) {
    return name;
}

Temp::Temp(void) {
    offset = INT_MAX;
}

Temp::Temp(int id, string name, int size, int offset) {
    this->id = id;
    this->name = name;
    this->size = size;
    this->offset = offset;
}

Temp *Temp::createTempI4(void) {
    int id = (Temp::tempCount)++;
    return new Temp(id, "_T" + id, 4, INT_MAX);
}


Temp *Temp::createConstTemp(int value) {
    map<int, Temp*>::iterator it = (Temp::constTempPool)->find(value);

    if (it == (Temp::constTempPool)->end()) {
        Temp *temp = new Temp();
        temp->isConst = true;
        temp->value = value;
        temp->name = itoa(value);
        (*(Temp::constTempPool))[value] = temp;
        return temp;
    } else {
        return it->second;
    }
}

bool Temp::isOffsetFixed(void) {
    return offset != INT_MAX;
}

/// \brief @Override
/// @FIXME
bool Temp::equals(Temp *temp) {
    return id == temp->id;
}

/// \brief @Override
int Temp::hashCode(void) {
    return id;
}

/// \brief @Override
string Temp::toString(void) {
    return name;
}



Tac::Tac(tacKind opc, Temp *op0) {
    this->opc = opc;
    this->op0 = op0;
    this->op1 = 0;
    this->op2 = 0;
}

/// \brief create Tac: a := op b
Tac::Tac(tacKind opc, Temp *op0, Temp *op1) {
    this->opc = opc;
    this->op0 = op0;
    this->op1 = op1;
    this->op2 = 0;
}

/// \brief create Tac: a := b op c
Tac::Tac(tacKind opc, Temp *op0, Temp *op1, Temp *op2) {
    this->opc = opc;
    this->op0 = op0;
    this->op1 = op1;
    this->op2 = op2;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, string str) {
    this->opc = opc;
    this->str = str;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, Temp *op0, string str) {
    this->opc = opc;
    this->op0 = op0;
    this->str = str;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, Temp *op0, VTable *vt) {
    this->opc = opc;
    this->op0 = op0;
    this->vt = vt;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, Label *label) {
    this->opc = opc;
    this->label = label;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, Temp *op0, Label *label) {
    this->opc = opc;
    this->op0 = op0;
    this->label = label;
}

Tac *Tac::emitAdd(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_ADD, dst, src1, src2);
}

Tac *Tac::emitSub(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_SUB, dst, src1, src2);
}

Tac *Tac::emitMul(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_MUL, dst, src1, src2);
}

Tac *Tac::emitDiv(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_DIV, dst, src1, src2);
}

Tac *Tac::emitMod(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_MOD, dst, src1, src2);
}

Tac *Tac::emitNeg(Temp *dst, Temp *src) {
    return new Tac(TAC_NEG, dst, src);
}

Tac *Tac::emitLAnd(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_LAND, dst, src1, src2);
}

Tac *Tac::emitLOr(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_LOR, dst, src1, src2);
}

Tac *Tac::emitLNot(Temp *dst, Temp *src) {
    return new Tac(TAC_LNOT, dst, src);
}

Tac *Tac::emitGtr(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_GTR, dst, src1, src2);
}

Tac *Tac::emitGeq(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_GEQ, dst, src1, src2);
}

Tac *Tac::emitEqu(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_EQU, dst, src1, src2);
}

Tac *Tac::emitNeq(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_NEQ, dst, src1, src2);
}

Tac *Tac::emitLeq(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_LEQ, dst, src1, src2);
}

Tac *Tac::emitLes(Temp *dst, Temp *src1, Temp *src2) {
    return new Tac(TAC_LES, dst, src1, src2);
}

Tac *Tac::emitAssign(Temp *dst, Temp *src) {
    return new Tac(TAC_ASSIGN, dst, src);
}

Tac *Tac::emitLoadVtbl(Temp *dst, VTable *vt) {
    return new Tac(TAC_LOAD_VTBL, dst, vt);
}

Tac *Tac::emitIndirectCall(Temp *dst, Temp *func) {
    return new Tac(TAC_INDIRECT_CALL, dst, func);
}

Tac *Tac::emitDirectCall(Temp *dst, Label *func) {
    return new Tac(TAC_DIRECT_CALL, dst, func);
}

Tac *Tac::emitReturn(Temp *src) {
    return new Tac(TAC_RETURN, src);
}

Tac *Tac::emitBranch(Label *label) {
    label->target = true;
    return new Tac(TAC_BRANCH, label);
}

Tac *Tac::emitBeqz(Temp *cond, Label *label) {
    label->target = true;
    return new Tac(TAC_BEQZ, cond, label);
}

Tac *Tac::emitBnez(Temp *cond, Label *label) {
    label->target = true;
    return new Tac(TAC_BNEZ, cond, label);
}

Tac *Tac::emitLoad(Temp *dst, Temp *base, Temp *offset) {
    if (!offset->isConst) {
        cerr << "offset must be constant" << endl;
        exit(-1);
    }

    return new Tac(TAC_LOAD, dst, base, offset);
}

Tac *Tac::emitStore(Temp *src, Temp *base, Temp *offset) {
    if (!offset->isConst) {
        cerr << "offset must be constant" << endl;
        exit(-1);
    }

    return new Tac(TAC_STORE, src, base, offset);
}

Tac *Tac::emitLoadImm4(Temp *dst, Temp *val) {
    if (!val->isConst) {
        cerr << "value must be constant" << endl;
        exit(-1);
    }

    return new Tac(TAC_LOAD_IMM4, dst, val);
}

Tac *Tac::emitLoadStrConst(Temp *dst, string str) {
    return new Tac(TAC_LOAD_STR_CONST, dst, str);
}

Tac *Tac::emitMark(Label *label) {
    Tac *mark = new Tac(TAC_MARK, label);
    label->where = mark;
    return mark;
}

Tac *Tac::emitParm(Temp *src) {
    return new Tac(TAC_PARM, src);
}

string Tac::binanyOpToString(string op) {
    return op0->name + " = (" + op1->name + " " + op + " " + op2->name + ")";
}

string Tac::unaryOpToString(string op) {
    return op0->name + " = " + op + " " + op1->name;
}

string Tac::toString(void) {
    switch (opc) {
        case TAC_ADD:
            return binanyOpToString("+");
        case TAC_SUB:
            return binanyOpToString("-");
        case TAC_MUL:
            return binanyOpToString("*");
        case TAC_DIV:
            return binanyOpToString("/");
        case TAC_MOD:
            return binanyOpToString("%");
        case TAC_NEG:
            return unaryOpToString("-");
        case TAC_LAND:
            return binanyOpToString("&&");
        case TAC_LOR:
            return binanyOpToString("||");
        case TAC_LNOT:
            return unaryOpToString("!");
        case TAC_GTR:
            return binanyOpToString(">");
        case TAC_GEQ:
            return binanyOpToString(">=");
        case TAC_EQU:
            return binanyOpToString("==");
        case TAC_NEQ:
            return binanyOpToString("!=");
        case TAC_LEQ:
            return binanyOpToString("<=");
        case TAC_LES:
            return binanyOpToString("<");
        case TAC_ASSIGN:
            return op0->name + " = " + op1->name;
        case TAC_LOAD_VTBL:
            return op0->name + " = VTBL <" + vt->name + ">";
        case TAC_INDIRECT_CALL:
            if (op0 != 0) {
                return op0->name + " = " + " call " + op1->name;
            } else {
                return "call " + op1->name;
            }
        case TAC_DIRECT_CALL:
            if (op0 != 0) {
                return op0->name + " = " + " call " + label->name;
            } else {
                return "call " + label->name;
            }
        case TAC_RETURN:
            if (op0 != 0) {
                return "return " + op0->name;
            } else {
                return "return <empty>";
            }
        case TAC_BRANCH:
            return "branch " + label->name;
        case TAC_BEQZ:
            return "if (" + op0->name + " == 0) branch " + label->name;
        case TAC_BNEZ:
            return "if (" + op0->name + " != 0) branch " + label->name;
        case TAC_LOAD:
            if (op2->value >= 0) {
                return op0->name + " = *(" + op1->name + " + " + op2->value + ")";
            } else {
                return op0->name + " = *(" + op1->name + " - " + (-op2->value)
                    + ")";
            }
        case TAC_STORE:
            if (op2->value >= 0) {
                return "*(" + op1->name + " + " + op2->value + ") = " + op0->name;
            } else {
                return "*(" + op1->name + " - " + (-op2->value) + ") = "
                    + op0->name;
            }
        case TAC_LOAD_IMM4:
            return op0->name + " = " + op1->value;
        case TAC_LOAD_STR_CONST:
            return op0->name + " = " + str;
        case TAC_MARK:
            return label->name + ":";
        case TAC_PARM:
            return "parm " + op0->name;
        default:
            return "";
            break;
    }
}
