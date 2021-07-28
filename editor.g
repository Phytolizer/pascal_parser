{
#include "editor.hpp"
}

LocatedElement: 
    Editor 
    | 
    AbstractElement 
    | 
    Element
    |
    Format
    |
    Color
    |
    Font
    |
    Indent
    ;

Editor:
    String AbstractElement+
    ;

AbstractElement:
    Block
    |
    GroupElement
    ;

Block:
    String String
    ;


