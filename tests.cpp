#include "catch.h"
#include "expr.h"
#include "cmdline.h"

TEST_CASE( "equals" ) {
    SECTION("NumExpr") {
        CHECK((new NumExpr(1))->equals(new NumExpr(1)) == true);
        CHECK((new NumExpr(1))->equals(new NumExpr(2)) == false);
        CHECK((new NumExpr(1))->equals(new VarExpr("x")) == false);
    }
    SECTION("VarExpr") {
        CHECK((new VarExpr("x"))->equals(new VarExpr("y")) == false);
        CHECK((new VarExpr("x"))->equals(new NumExpr(1)) == false);
        CHECK((new VarExpr("x"))->equals(new VarExpr("x")) == true);
    }
    SECTION("AddExpr") {
        CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new NumExpr(2), new NumExpr(3))) ==
              true);
        CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new NumExpr(3), new NumExpr(2))) ==
              false);

        CHECK((new AddExpr(new NumExpr(2), new NumExpr(2)))->equals(new MultExpr(new NumExpr(7), new NumExpr(3))) ==
              false);
        CHECK((new AddExpr(new NumExpr(2), new NumExpr(2)))->equals(new MultExpr(new NumExpr(2), new NumExpr(2))) ==
              false);
    }

    SECTION("MultExpr") {
        CHECK((new MultExpr(new NumExpr(2), new NumExpr(2)))->equals(new AddExpr(new NumExpr(1), new NumExpr(2))) ==
              false);
        CHECK((new MultExpr(new NumExpr(2), new NumExpr(2)))->equals(new AddExpr(new NumExpr(2), new NumExpr(2))) ==
              false);

        CHECK((new MultExpr(new NumExpr(2), new NumExpr(2)))->equals(new MultExpr(new NumExpr(2), new NumExpr(2))) ==
              true);
        CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))->equals(new MultExpr(new NumExpr(2), new NumExpr(1))) ==
              false);
    }
}

TEST_CASE("Interp") {
    MultExpr *complexExprWithVar = new MultExpr(
            new AddExpr(new VarExpr("x"), new MultExpr(new NumExpr(2), new NumExpr(3))), new NumExpr(3));
    MultExpr *complexExprWithNoVar = new MultExpr(
            new AddExpr(new NumExpr(2), new MultExpr(new NumExpr(2), new NumExpr(3))), new NumExpr(3));

    SECTION("NumExpr") {
        CHECK((new NumExpr(3))->interp() == 3);
    }
    SECTION("AddExpr") {
        CHECK((new AddExpr(new NumExpr(3), new NumExpr(9)))->interp() == 12);
    }
    SECTION("MultExpr") {
        CHECK((new MultExpr(new NumExpr(3), new NumExpr(9)))->interp() == 27);
    }
    SECTION("VarExpr") {
        CHECK_THROWS_WITH((new VarExpr("x"))->interp(), "VarExpr has no interpretable value");
    }
    SECTION("ComplexExpressions") {
        CHECK((complexExprWithNoVar->interp() == 24));
        CHECK_THROWS_WITH(complexExprWithVar->interp(), "VarExpr has no interpretable value");
    }
}

TEST_CASE("has_variable") {
    MultExpr *complexExprWithVar = new MultExpr(
            new AddExpr(new VarExpr("x"), new MultExpr(new NumExpr(2), new NumExpr(3))), new NumExpr(3));
    MultExpr *complexExprWithNoVar = new MultExpr(
            new AddExpr(new NumExpr(2), new MultExpr(new NumExpr(2), new NumExpr(3))), new NumExpr(3));
    SECTION("NumExpr") {
        CHECK((new NumExpr(3))->has_variable() == false);
    }
    SECTION("AddExpr") {
        CHECK((new AddExpr(new NumExpr(3), new NumExpr(9)))->has_variable() == false);
        CHECK((new AddExpr(new NumExpr(3), new VarExpr("y")))->has_variable() == true);
    }
    SECTION("MultExpr") {
        CHECK((new MultExpr(new NumExpr(3), new NumExpr(9)))->has_variable() == false);
        CHECK((new MultExpr(new VarExpr("x"), new NumExpr(9)))->has_variable() == true);
    }
    SECTION("VarExpr") {
        CHECK((new VarExpr("x"))->has_variable() == true);
    }
    SECTION("ComplexExpressions") {
        CHECK((complexExprWithVar)->has_variable() == true);
        CHECK((complexExprWithNoVar)->has_variable() == false);
    }
}

TEST_CASE("subst"){
    MultExpr* complexExprWithVar = new MultExpr(new AddExpr(new VarExpr("x"), new MultExpr(new NumExpr(2), new NumExpr(3))), new NumExpr(3));
    MultExpr* complexExprWithNoVar = new MultExpr(new AddExpr(new NumExpr(2), new MultExpr(new NumExpr(2), new NumExpr(3))), new NumExpr(3));

    SECTION("NumExpr"){
        CHECK((new NumExpr(2))->subst("x", new NumExpr(3))->equals(new NumExpr(2)) == true);
    }
    SECTION("AddExpr"){
        CHECK(((new AddExpr(new NumExpr(3), new NumExpr(9)))->subst("x", new NumExpr(2)))->equals(new AddExpr(new NumExpr(3), new NumExpr(9))) == true);
        CHECK((new AddExpr(new NumExpr(3), new VarExpr("y")))->subst("x", new NumExpr(2))->equals(new AddExpr(new NumExpr(3), new VarExpr("y"))) == true);
        CHECK((new AddExpr(new NumExpr(3), new VarExpr("x")))->subst("x", new NumExpr(2))->equals(new AddExpr(new NumExpr(3), new NumExpr(2))) == true);
        CHECK((new AddExpr(new NumExpr(3), new VarExpr("x")))->subst("x", new VarExpr("y"))->equals(new AddExpr(new NumExpr(3), new VarExpr("y"))) == true);
    }
    SECTION("MultExpr") {
        CHECK((new MultExpr(new NumExpr(3), new NumExpr(9)))->subst("x", new NumExpr(2))->equals(new MultExpr(new NumExpr(3), new NumExpr(9))) == true);
        CHECK((new MultExpr(new NumExpr(3), new VarExpr("y")))->subst("x", new NumExpr(2))->equals(new MultExpr(new NumExpr(3), new VarExpr("y"))) == true);
        CHECK((new MultExpr(new NumExpr(3), new VarExpr("x")))->subst("x", new NumExpr(2))->equals(new MultExpr(new NumExpr(3), new NumExpr(2))) == true);
        CHECK((new MultExpr(new NumExpr(3), new VarExpr("x")))->subst("x", new VarExpr("y"))->equals(new MultExpr(new NumExpr(3), new VarExpr("y"))) == true);
    }
    SECTION("VarExpr"){
        CHECK((new VarExpr("y"))->subst("x", new NumExpr(2))->equals(new VarExpr("y")) == true);
        CHECK((new VarExpr("x"))->subst("x", new NumExpr(2))->equals(new NumExpr(2)) == true);
        CHECK((new VarExpr("x"))->subst("x", new VarExpr("y"))->equals(new VarExpr("y")) == true);
    }
}


