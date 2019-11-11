# Data analysis of SMHI data

In the project we have produced script using Bash, C++ and ROOT to clean up raw data, analyze it and make some plots.
The report can be found as the pdf weatherreport.pdf.
The project is divided in three parts, as described in the report.

## Getting Started
To be sure that everything works, the script has been tested on the following versions:
```
Use root version 5.34/30
On Lubuntu (32-bit)
C++ version: 5.4.0 2016/06/09
```
### Prerequisites

What things you need to install the software and how to install them

```
Bash, Ubuntu, C++ in the above mentioned versions.
```

### Order of running scripts

To run Project A and B, simply cd into code directory and type
```
.L root -l
```

The plots should be shown and saved in /images and /plots.

If you want to extrapolate to a certain year, call TempTrender:tempPerYear(int yearToExtrapolate) while in root:

```
t.tempPerYear(int yearToExtrapolate)
```

To run Project C that shows the number of days that have an daily average temperature below 0 in each year,
 run the file in the directory /Cleandata named cleaning_data.sh (WARNING! The code is slow and it can take up to 30 min to finish!!)

## Authors

* **Leo Zethraeus**
* **Piotr Yartsev**
* **Xi-Zhen Liu**

