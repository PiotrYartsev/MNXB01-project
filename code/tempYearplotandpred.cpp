
#include <iostream>
#include "tempTrender.h"
// include C++ STL headers 
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TH2.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TString.h>
#include <TRandom.h>
#include <TGraph.h>
#include <TGaxis.h>
#include <TLegend.h>





/* 
Root function to plot histograms of the annual average temperatures from the annualtemp.txt data set, and to extrapolate temperature to a year given by user input.
* Make sure to run annualtemp.cpp and movingmean.cpp first, in that order.
* By: Leo Zethraeus
*/

//Input: the year you want to extrapolate to, or estimate the future temperature, in other words. Output: the estimated temperature that year.


double tempYearplotandpred(Int_t input_year) 
	{
	  
	  gStyle->SetOptStat(0);
	  gStyle->SetOptFit(0);
	  Double_t total_mean = 0.;
	  Int_t first_year = 1722;
	  Int_t last_year = 2013;
	  Int_t interval = int(last_year - first_year+1);
	  Double_t temp[interval];

	  cout << "interval: " << interval << endl;

	  //First run annualtemp.cpp to compute the annual average temperatures per mean, then input the annualtemp.txt produced here.
	  ifstream infile("../ProcessedData/UppsalaData/annualtemp.txt");
	  if(!infile) {
				std::cout << "Error, run annualtemp.cpp first" << endl;
				return 1;
				}

	  Double_t year[interval];
	  double tem = 0.;
	  double tem_sum = 0;
	  int ye = 0;
	  int yr = 0;
	  
	  while(infile >> yr >> tem){

			  temp[ye] = tem;
			  tem_sum += tem;
			  year[ye] = yr;
			  ++ye;
		  }
	  total_mean = tem_sum/ye;
	  cout << "TOTAL MEAN: " << total_mean << endl;
		
	  infile.close();
		  
	  //Open file and fill temp with the average temperatures.
	  
	  cout << "Plotting yearly averages from: " << first_year << " to " << last_year << endl;
		
	  TH1D* upTemp = new TH1D("upTemp","Annual average temperature in Uppsala 1722-2013; year; Temperature (Celsius)" , interval, first_year, last_year);
	  TH1D* downTemp = new TH1D("downTemp","Temperatures below average; year; Temp" , interval, first_year, last_year);
	  TH1D* totalTemp = new TH1D("TotalTemp","Total temp; year; Temp" , interval, first_year, last_year);
		
		
	  //open file with data and fill histograms. I actually have to shift the data -total_mean to be able to plot the nice upside-down histogram, to shift it back for the plot I manually change the Y-axis.
		
	  for(int y = 0; y < interval; ++y){
			//cout << "year: " << y << " temp: " << temp[y] << endl;
			totalTemp->Fill(y+first_year,temp[y]-total_mean);
			
		  if(temp[y] > total_mean){
				downTemp->Fill(y+first_year, total_mean-total_mean);
				upTemp->Fill(y+first_year,temp[y]-total_mean);
				}
		  else if(temp[y] <= total_mean){
				downTemp->Fill(y+first_year,temp[y]-total_mean);
				upTemp->Fill(y+first_year,total_mean-total_mean);
				}
			}
			
		//Set some graphics and perform the fit on the total temperature.	
	  gStyle->SetOptStat(111111);
	  gStyle->SetOptFit(1111111);
	  TF1* fitFunc = new TF1("fitFunc", "pol4", first_year, last_year);
	  fitFunc->SetParameter(-3,3);
	  fitFunc->SetLineColor(1);
	  fitFunc->SetLineStyle(9);
	  fitFunc->SetLineWidth(4);
	  fitFunc->SetName("Fitted function");
	  totalTemp->Fit(fitFunc);
	  double extratemp = fitFunc->Eval(input_year) + total_mean;
	  
	  cout << "Extrapolating to year " << input_year << ": " << fixed << setprecision(4)<<extratemp<< " celsius."<< endl;
	  
	  
	  
		
		TCanvas* c1 = new TCanvas("c1", "Annual average temperature in Uppsala", 900, 600);
		TGaxis *y_axis = new TGaxis(first_year,-4,first_year,4, -4+total_mean, 4+total_mean, 510);
		
		upTemp->GetYaxis()->SetLabelSize(0.3);

		upTemp->SetFillColor(kRed);
		upTemp->Draw("B");
		upTemp->GetYaxis()->SetBinLabel(1, " ");
		upTemp->SetAxisRange(-3.,5.,"Y");
		
		downTemp->SetFillColor(kBlue);
		downTemp->Draw("SAME");
		fitFunc->Draw("SAME");
		y_axis->Draw();
		TLegend* legend = new TLegend(0.5,0.8,0.88,0.9);
	   legend->AddEntry(upTemp,"Temperature above average","f");
	   legend->AddEntry(downTemp,"Temperature below average","f");
	   legend->AddEntry("Fitted function","Fitted pol4","l");
	   legend->Draw();
	   
	   TH1D* hist = new TH1D("hist","Moving average; year; Temp" , interval, first_year, last_year);
	   
	   
	   
	/*
	 The Code below reads and plots the moving mean on the existing canvas:
	  
	 */
	 //First run code movingmean.cpp with boxinterval 5, or change name accordingly.   
	 ifstream infile2("../ProcessedData/UppsalaData/movingboxmeantemp.txt");
		if(!infile2) {
				std::cout << "Error, run movingmean.cpp first" << endl;
				return 1;
				}
	  
	  int interval2 = 58; //98;//14; //56 is the number of entries in the "movingboxmeantemp.txt" file (default box_interval = 5), change to 98 for "moving3boxmeantemp.txt" or 14 for "moving20boxmeantemp.txt" for example
	  Double_t mov_temp[interval2];
	  Double_t year2[interval2];
	  double tem1 = 0.;//5.2;
	  int ye2 = 0;
	  int yr1 = 0;
	  int yr2 = 0;
	  
	  while(infile2 >> yr1 >> yr2 >> tem1){
		  mov_temp[ye2] = tem1;
		  year2[ye2] = yr1+2;
		  ++ye2;
		  }
		  	
	  infile2.close();
	   
		for(int y = 0; y < interval2; ++y){
			hist->Fill(year2[y],mov_temp[y]-total_mean);
		  }

		
	hist->SetLineWidth(2);
	hist->SetMarkerStyle(22);
	hist->SetLineColor(kGreen);
	hist->SetName("Moving Mean");
	hist->Draw("SAME C");
	legend->AddEntry("Moving Mean","Moving Mean, 5-year interval","l");
	
	  // Save the canvas as a picture
	c1->SaveAs("../Plots/tempYear.png");

	//Output the reduced chi-square of the fitted fourth degree polynomial and return the extrapolated temperature:
	cout << "Reduced Chi²: " << (fitFunc->GetChisquare()/fitFunc->GetNDF()) << endl;
	return extratemp;
		
	}
