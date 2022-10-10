#include <assert.h>
#include "check_parentheses.h"

int main() {
   char parentheses1[] = "<>[]{}()";
   char parentheses2[] = "<>ab[]{}()";
   char expression1[] = "cvcv{a()b[c()]}<s<>>";
   char expression2[] = "{aa}()<cv({}<>)>";
   char expression3[] = "vcv[(])q";
   char expression4[] = "{{[]]s}q}";
   assert(check_parentheses(expression1, parentheses1));
   assert(check_parentheses(expression2, parentheses1));
   assert(!check_parentheses(expression3, parentheses1));
   assert(!check_parentheses(expression4, parentheses1));

   assert(check_parentheses(expression1, parentheses2));
   assert(!check_parentheses(expression2, parentheses2));
   assert(!check_parentheses(expression3, parentheses2));
   assert(!check_parentheses(expression4, parentheses2));
   return 0;
}



