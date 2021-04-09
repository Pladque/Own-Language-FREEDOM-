# Own-Language
## Freedom is a dynamic typed programming languge whose main feature are changable keywords
### With Freedom you can recreate languages like Rockstar or ArnoldC

## Features:

- [X] Variables
- [X] Loops
- [X] If statemant
- [X] dynamic keywords
- [ ] Stringlike wariables
- [ ] Arrays

## Usage:
Just run main.cpp and you are ready to go!

## Syntax:
### Build-in debug commands:
- "ordrs" - print last interpreted orders
- "opnf -n -rn a.in" - open file (-n for name, -rn for run, a.in is a name of file)
- "toks" - print tokens
- actvars - print active variables
- rstrt - restarts Core, recommended if you want run same program twice (otherwise variables, changed keywords will not be cleared)
### Printing sth:
To print any word you can just write it in the code (in new line or between " ; ")
If that word is not a variable, it will be just print to the console
### Comments:
To commant some code, just use "//  my commant"
(2 spaces after "//" are required"
### declaring variable:
Basic declaration:
```
var  variable  =  15  ;
var  variable   ;
```
Value by words:

*if you are familiar with rockstar leanguge- in mine it works the same*
```
var  variable  =   whats  the  value  of   it?   ;
```
That varaible will be equal 53523 ("whats" has 5 letters, "the" has 3, and so on...)

### If and loops:
```
var variable  =  9
if variable  >   word
   my variable is bigger then word     //   indentation is just for estetic, you dont have to style code that way
stopif
```
*You dont have to use ";" if you are running code from file and you have new lines*
```
var  variable   =   9
while  variable  >   word
   variable  =   variable  -  hey    
stop
variable
```
Expected output:
```
2
```
## Important: Every element should be seperated by 2 spaces (or single tab)
### Arthmetic Operators :   +, -, *, /, ^
### Logic Operators: >, >=, <, <=, ==

## Changing keywords:
```
+  ===  plus  ;
[old keyword]  ===   [new keyword]
```
Old keyword will be deleted from operators, you cab even change "===" operator
```
===  ===  multiple words operator
```
Here I changed operator === to "multiple words operator"
