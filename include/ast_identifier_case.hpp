// identifier is called in different ways, I (Clyde) decided that I could deal with this using an scoped enum.

#pragma once
namespace ast {
enum class IdentifierCase{
    DEFAULT,
    DECL, // global variables
    FUNCT,
    ARRAY,
    // the ones below can't be done globally (GodBolt doesn't do it)
    LOCAL_INIT, // initialising inside a function (int x = 7)
    LOCAL_OPER, // variable operation (x + y)
    LOCAL_OVERWRITE // variable reassignment (x = 3)
};

// the idea is that you can pass this like { $$ = new Identifier($1, IdentifierCase::DECL); } and then go ham from there
}
