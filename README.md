## "Metaprogramming for the brave" presentation for [C++Now][] 2016

This repository contains my [reveal.js][]-based presentation on metaprogramming
for dummies for C++Now 2016.

## Basic usage
Go to https://ldionne.github.io/cppnow-2016-metaprogramming-for-the-brave or
open `index.html` with your browser. Note that opening `index.html` with your
browser does not work on Google Chrome due to [this issue][chrome].

## Advanced usage
From the root of the repository,
```sh
npm install
grunt serve &
```

and then connect to `localhost:8000` to view locally. To build the code samples
and benchmarks, issue the following from the root of the repository

```sh
mkdir build
cd build
cmake ..
cmake --build . --target install-dependencies # install required dependencies
cmake --build . --target samples # build the code samples
cmake --build . --target check # build and test the code samples
cmake --build . --target benchmarks # generate the benchmarks
```

<!-- Links -->
[C++Now]: http://cppnow.org
[reveal.js]: https://github.com/hakimel/reveal.js
[chrome]: http://stackoverflow.com/q/4819060/627587
