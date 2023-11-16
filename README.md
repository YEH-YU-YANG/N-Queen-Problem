# N-Queen-Problem

Write programs in `C++` to solve the n-queen problem.
1. Use `Iterative Deepening Search (IDS) `
2. Use `Hill Climbing (HC)`
3. Use `Genetic Algorithm (GA)`

`report.pdf` is my research report. Write in Mandarin. <br>
`N-Queen Problem Record.xlsx` is research recording of 8-Queens、50 Queens solved with IDS、HC、GA algorithm.

## IDS

compile .cpp
```
g++ IDS.cpp -o IDS.exe
```

Solve 8-Queens problem with IDS algorithm <br>
Outputfile: `IDS_8_Queens.txt`
```
.\IDS.exe 8
```

Solve 50-Queens problem with IDS algorithm<br>
Outputfile: `IDS_50_Queens.txt`
```
.\IDS.exe 50
```

## HC

compile .cpp
```
g++ HC.cpp -o HC.exe
```

Solve 8-Queens problem with HC algorithm <br>
Outputfile: `HC_8_Queens.txt`
```
.\HC.exe 8
```

Solve 50-Queens problem with HC algorithm <br>
Outputfile: `HC_50_Queens.txt`
```
.\HC.exe 50
```

## GA

compile .cpp
```
g++ GA.cpp -o GA.exe
```

Solve 8-Queens problem with GA algorithm <br>
Outputfile: `GA_8_Queens.txt`
```
.\GA.exe 8
```

Solve 50-Queens problem with GA algorithm <br>
Outputfile: `GA_50_Queens.txt`
```
.\GA.exe 50
```

## 30times.py

Execution
```
.\30times.py 8   -> 8  Queen
.\30times.py 50  -> 50 Queen
.\30times.py N   -> N  Queen
```
This aims to generate output automatically. <br>

It will solve N-Queens problem with HC or GA algorithm and generate output 30 times.<br>
( Or you can modify parameter of output times in 30times.py ) <br>

Outputs will be generate in `Result.xlsx` automatically.
