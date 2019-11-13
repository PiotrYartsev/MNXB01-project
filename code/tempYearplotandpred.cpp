
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
* Make sure to run annualtemp.cpp first. Done automatically if you call project() or TempTrender::tempPerYear(int yearToExtrapolate) in root.
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
		
	  TH1D* upTemp = new TH1D("upTemp","Annual average temperature in Uppsala 1722-2013; year; Temperature [#circ C]" , interval, first_year, last_year);
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
	  fitFunc->SetLineColor(kGreen);
	  fitFunc->SetLineStyle(9);
	  fitFunc->SetLineWidth(4);
	  fitFunc->SetName("Fitted function");
	  totalTemp->Fit(fitFunc);
	  double extratemp = fitFunc->Eval(input_year) + total_mean;
	  cout << endl;
	  //Output the reduced chi-square of the fitted fourth degree polynomial and return the extrapolated temperature:
	  cout << "Reduced Chi² from fit: " << (fitFunc->GetChisquare()/fitFunc->GetNDF()) << endl;
	  cout << endl;
	  cout << "Extrapolating to year " << input_year << ": " << fixed << setprecision(1)<<extratemp<< " celsius."<< endl << endl;
	  
	  
	  
		
		TCanvas* c1 = new TCanvas("c1", "Annual average temperature in Uppsala", 900, 600);
		TGaxis *y_axis = new TGaxis(first_year,-4,first_year,4, -7+total_mean, 7+total_mean, 510);
		
		upTemp->GetYaxis()->SetLabelSize(0.3);

		upTemp->SetFillColor(kRed);
		upTemp->Draw("B");
		upTemp->GetYaxis()->SetBinLabel(1, " ");
		upTemp->SetAxisRange(-3.,5.,"Y");
		
		downTemp->SetFillColor(kBlue);
		downTemp->Draw("SAME");
		fitFunc->Draw("SAME");
		
		y_axis->SetLabelSize(0.04);
		y_axis->SetNdivisions(19);
		y_axis->Draw();
		TLegend* legend = new TLegend(0.5,0.8,0.88,0.95);
	    legend->AddEntry(upTemp,"Temperature above average","f");
	    legend->AddEntry(downTemp,"Temperature below average","f");
	    legend->AddEntry("Fitted function","Fitted pol4","l");
	    legend->SetTextSize(0.025);
	    legend->Draw();
	   
	// Below code creates a nice graph for the moving mean with 2*box_interval = 10 years.
	int box_interval = 5;	  
	TGraph* graph = new TGraph();
	for(int bin = box_interval; bin < interval - box_interval; bin += box_interval) {
		double mov_mean = 0;
		
		for(int k = -box_interval; k <= box_interval; ++k) {
			mov_mean += (temp[bin+k]/(2*box_interval+1));
			}
		
		graph->SetPoint(graph->GetN(), totalTemp->GetBinCenter(bin), mov_mean-total_mean);
	}
	graph->SetLineWidth(4);
	graph->SetLineColor(kBlack);
	
		
	//Make a new graph with moving means of 2*box_interval = 20 years.	
	
	int box_interval2 = 10;	  
	TGraph* graph2 = new TGraph();
	  
	for(int bin = box_interval2; bin < interval - box_interval2; bin += box_interval2) {
		double mov_mean2 = 0;
		  
		for(int k = -box_interval2; k <= box_interval2; ++k) {
			mov_mean2 += (temp[bin+k]/(2*box_interval2+1));
			}
			
			graph2->SetPoint(graph2->GetN(), totalTemp->GetBinCenter(bin), mov_mean2-total_mean);
		}
	  
		graph2->SetLineWidth(3);
		graph2->SetLineColor(kGray+2);
		graph->SetName("Moving Mean");
		graph->Draw("SAME C");
		graph2->SetName("Moving Mean,20");
		graph2->Draw("SAME C");
		
		legend->AddEntry("Moving Mean","Moving Mean, 10-year interval","l");
		legend->AddEntry("Moving Mean,20","Moving Mean, 20-year interval","l");
		
		  // Save the canvas as a picture
		
		c1->SaveAs("../Plots/tempYear.png");
		return extratemp;
		
	}
