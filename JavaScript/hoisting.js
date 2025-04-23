// Code section - 1
console.log("----- Section 1 -----");


var x = 7;

function fun(){
    console.log("Hey! I am inside the function")
}

console.log(x);
fun()

/*
    The above code run successfully! basic stuff. Now Try running section - 2
*/
console.log("----- Section 2 -----")

console.log(y)
console.log(fun2)
fun2()

var y = 10;
function fun2(){
    console.log("Hey!, I am inside the function 2 ")
}

console.log(fun2)

/*
    Now it prints the value of y as "undefined"

    So, basically JS executes its code in 2 phase: Memeory Allocation and Code Execution
    ->  In memory allocation phase it goes through the code and assign memory to all variables and functions(the entire function code is copied as it is!) in the "variable environment".
        The values assinged to the variables are "undefined" in this phase.
        Thus, we can access the function and variables even before they are initialized!
    
    ->  In code execution phase, code is ecexuted line by line. (It is executed in the space called "Thread of Execution")
        If fuction is encountered, again the execution context for that function is created inside the Thread of Execution.

    This is called Hoisting: A behavior where JS where declaration of variables, function and classes are moved on top of their scope before code
    execution. This allows the programmer to use them even before they are declared in the code. 
*/

// What wait? does arrow functions get hoisted? ===> NO!
console.log("----- Section 3 -----")

const arrowFun1 = () => {
    console.log("I am the 1st arrow function!")
}

arrowFun1()

// comment out the code below and run ==> you will get an error ["ReferenceError: Cannot access 'arrowFun2' before initialization"]
//arrowFun2()

const arrowFun2 = () => {
    console.log("I am the 2nd arrow function!")
}




