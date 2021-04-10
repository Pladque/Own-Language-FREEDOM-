# Own-Language
## Freedom is a dynamic typed programming languge whose main feature are changable keywords
### With Freedom you can recreate languages like Rockstar or ArnoldC

## Features:

- [X] Variables
- [X] Loops
- [X] If statemant
- [X] dynamic keywords
- [X] Stringlike wariables
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

You can also declar string variable:
```
var  some word variable  ~~  my first words
var  another variable  ~~  some word variable  and my other
some word
another variable
```
Expected output:
```
my first words
my first words  and my other
```
With changing value it works same as with numbers, For example:
```
another variable  ~~  new value of thos string  
```

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
3
```
## Important: Every element should be seperated by 2 spaces (or single tab)
### Arthmetic Operators :   
> +, -, *, /, ^, %
### Logic Operators:
> \>, >=, <, <=, ==

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
# EXAMPLE CODE:
## FizzBuzz (basic)
```
var  counter  =  0
var  RANGE  =  100
 
while  counter  <  RANGE
	var  result  ~~ 
	if  counter   %  3  ==  0
		result  ~~  fizz
	stopif

	if  counter  %  5  ==  0
		result  ~~  result  buzz
	stopif

	
	counter
	result
	
	counter  =  counter  +  1
	
stop
```
