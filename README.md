# DeterminingDataTypesInADynamicLanguage

- This is a ”compiler” program to determine or infer the data type of each variable. 
- The input source code is: Python. This “compiler”-style program is developed in C++. 
- The output is a list of variables with their data types, unless the data type cannot be determined. This list is alphabetically sorted. 
- This Program uses regular expression to recognize identifiers, numbers and strings. 
- This program will use a simplified context-free grammar to recognize arithmetic expressions with ’+’. In order to detect data types, I had to perform a partial evaluation using an attribute grammar to extend the parse tree. The data types in Python is: bool, int, str, list, undefined. 
