int check_parentheses(char expression[], char parentheses[]);
// parenthesis is supplied in format "<>(){}[]", i.e. consecutive closed pairs

int is_parentheses(char sym, char parentheses[]);

int is_opening(char sym, char parentheses[]);

int is_pair(char open, char close, char parentheses[]);
