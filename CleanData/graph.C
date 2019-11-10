{
	//Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   
   TCanvas *c1 = new TCanvas("c1","The nummber of winter days in Lulea over the years",200,10,700,500);

int i=0;
int n=65;
double x[n];

std::ifstream File("datasets/smhi-opendata_Lulea/data_years_smhi-opendata_Lulea.txt");
if(!File){
		std::cout << "Not in file \n";

}
for( std::string line; getline( File, line ); )
{
x[i]=atof(line.c_str());
std::cout << x[i];
i++;
}
File.close();


int l=0;
double y[n];

std::ifstream Filetwo("datasets/smhi-opendata_Lulea/Final.txt");

for( std::string line; getline( Filetwo, line ); )
{
y[l]=atof(line.c_str());
l++;
}
Filetwo.close();


   gr = new TGraph(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Days with average temperature bellow 0 each year");
   gr->GetXaxis()->SetTitle("Year");
   gr->GetYaxis()->SetTitle("Nummber of days");
   gr->Draw("ACP");
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
   c1->SaveAs("Lulea.pdf");
}
