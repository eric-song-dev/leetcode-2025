Tutorial: https://javascript.info/variables

Modern JavaScript supports “classes” and “modules” – advanced language structures (we’ll surely get to them), that enable use strict automatically. So we don’t need to add the "use strict" directive, if we use them.

When should we use capitals for a constant and when should we name it normally? Let’s make that clear.
Being a “constant” just means that a variable’s value never changes. But some constants are known before execution (like a hexadecimal value for red) and some constants are calculated in run-time, during the execution, but do not change after their initial assignment.
For instance:
const pageLoadTime = /* time taken by a webpage to load */;
The value of pageLoadTime is not known before the page load, so it’s named normally. But it’s still a constant because it doesn’t change after the assignment.
In other words, capital-named constants are only used as aliases for “hard-coded” values.

Such operators have the same precedence as a normal assignment, so they run after most other calculations:

```javascript
let n = 2;

n *= 3 + 5; // right part evaluated first, same as n *= 8

alert( n ); // 16
```

The ordinary break after input would only break the inner loop. That’s not sufficient – labels, come to the rescue!

A label is an identifier with a colon before a loop:

```javascript
labelName: for (...) {
  ...
}
```
The break <labelName> statement in the loop below breaks out to the label:

```javascript
outer: for (let i = 0; i < 3; i++) {

  for (let j = 0; j < 3; j++) {

    let input = prompt(`Value at coords (${i},${j})`, '');

    // if an empty string or canceled, then break out of both loops
    if (!input) break outer; // (*)

    // do something with the value...
  }
}

alert('Done!');
```



When a value is passed as a function parameter, it’s also called an argument.

In other words, to put these terms straight:

A parameter is the variable listed inside the parentheses in the function declaration (it’s a declaration time term).
An argument is the value that is passed to the function when it is called (it’s a call time term).
We declare functions listing their parameters, then call them passing arguments.

In the example above, one might say: “the function showMessage is declared with two parameters, then called with two arguments: from and "Hello"”.

```javascript
function sayHi() {
  alert( "Hello" );
}
```

```javascript
let sayHi = function() {
  alert( "Hello" );
};
```

Let’s reiterate: no matter how the function is created, a function is a value. Both examples above store a function in the sayHi variable.



Computed properties
We can use square brackets in an object literal, when creating an object. That’s called computed properties.

For instance:

```javascript
let fruit = prompt("Which fruit to buy?", "apple");

let bag = {
  [fruit]: 5, // the name of the property is taken from the variable fruit
};

alert( bag.apple ); // 5 if fruit="apple"
```

The meaning of a computed property is simple: [fruit] means that the property name should be taken from fruit.

So, if a visitor enters "apple", bag will become {apple: 5}.

Essentially, that works the same as:
```javascript
let fruit = prompt("Which fruit to buy?", "apple");
let bag = {};

// take property name from the fruit variable
bag[fruit] = 5;
```
…But looks nicer.


If you come from another programming language, then you are probably used to the idea of a “bound this”, where methods defined in an object always have this referencing that object.

In JavaScript this is “free”, its value is evaluated at call-time and does not depend on where the method was declared, but rather on what object is “before the dot”.


Usually, constructors do not have a return statement. Their task is to write all necessary stuff into this, and it automatically becomes the result.

But if there is a return statement, then the rule is simple:

If return is called with an object, then the object is returned instead of this.
If return is called with a primitive, it’s ignored.


But do we need this function? Can’t we just use the comparison === NaN? Unfortunately not. The value NaN is unique in that it does not equal anything, including itself:

```javascript
alert( NaN === NaN ); // false
```


An array is a special kind of object. The square brackets used to access a property arr[0] actually come from the object syntax. That’s essentially the same as obj[key], where arr is the object, while numbers are used as keys.

They extend objects providing special methods to work with ordered collections of data and also the length property. But at the core it’s still an object.

The insertion order is used
The iteration goes in the same order as the values were inserted. Map preserves this order, unlike a regular Object.


Arrow functions do not have "arguments"
If we access the arguments object from an arrow function, it takes them from the outer “normal” function.


Function Declarations
A function is also a value, like a variable.

The difference is that a Function Declaration is instantly fully initialized.

When a Lexical Environment is created, a Function Declaration immediately becomes a ready-to-use function (unlike let, that is unusable till the declaration).

That’s why we can use a function, declared as Function Declaration, even before the declaration itself.

Naturally, this behavior only applies to Function Declarations, not Function Expressions where we assign a function to a variable, such as let say = function(name)...

As we already know, a function in JavaScript is a value.
Every value in JavaScript has a type. What type is a function?
In JavaScript, functions are objects.
A good way to imagine functions is as callable “action objects”. We can not only call them, but also treat them as objects: add/remove properties, pass by reference etc.


Zero delay setTimeout
There’s a special use case: setTimeout(func, 0), or just setTimeout(func).

This schedules the execution of func as soon as possible. But the scheduler will invoke it only after the currently executing script is complete.

So the function is scheduled to run “right after” the current script.

For instance, this outputs “Hello”, then immediately “World”:
```javascript
setTimeout(() => alert("World"));

alert("Hello");
```
The first line “puts the call into calendar after 0ms”. But the scheduler will only “check the calendar” after the current script is complete, so "Hello" is first, and "World" – after it.

The finally clause works for any exit from try...catch. That includes an explicit return.

There can be only a single result or an error
The executor should call only one resolve or one reject. Any state change is final.

All further calls of resolve and reject are ignored

We can call .then on a Promise as many times as we want. Each time, we’re adding a new “fan”, a new subscribing function, to the “subscription list”. More about this in the next chapter: Promises chaining.


The whole thing works, because every call to a .then returns a new promise, so that we can call the next .then on it.
When a handler returns a value, it becomes the result of that promise, so the next .then is called with it.
A classic newbie error: technically we can also add many .then to a single promise. This is not chaining.



In case of an error, other promises are ignored
If one promise rejects, Promise.all immediately rejects, completely forgetting about the other ones in the list. Their results are ignored.
For example, if there are multiple fetch calls, like in the example above, and one fails, the others will still continue to execute, but Promise.all won’t watch them anymore. They will probably settle, but their results will be ignored.
Promise.all does nothing to cancel them, as there’s no concept of “cancellation” in promises. In another chapter we’ll cover AbortController that can help with that, but it’s not a part of the Promise API.


In a module, top-level this is undefined.
Compare it to non-module scripts, where this is a global object:
```javascript
<script>
  alert(this); // window
</script>

<script type="module">
  alert(this); // undefined
</script>
```

The notable difference of export ... from compared to import/export is that re-exported modules aren’t available in the current file. So inside the above example of auth/index.js we can’t use re-exported login/logout functions.

we can’t import conditionally or at run-time:
```javascript
if(...) {
  import ...; // Error, not allowed!
}

{
  import ...; // Error, we can't put import in any block
}
```

Although import() looks like a function call, it’s a special syntax that just happens to use parentheses (similar to super()).
So we can’t copy import to a variable or use call/apply with it. It’s not a function.


