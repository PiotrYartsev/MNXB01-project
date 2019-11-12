{
string Input;
	std::cin >> Input;
string Inputtwo;
	std::cin >> Inputtwo;
string Inputthree;
	std::cin >> Inputthree;
TCanvas *c1 = new TCanvas("c1","The nummber of winter days in Lulea over the years",200,10,700,500);

int i=0;
int n=54;
double x[n];

std::ifstream File(Input.c_str());
if(!File){
		std::cout << "Not in file  one \n";

}
for( std::string line; getline( File, line ); )
{
x[i]=atof(line.c_str());
std::cout << x[i] <<"\n";
i++;
}
File.close();


int l=0;
double y[n];
std::ifstream Filetwo(Inputtwo.c_str());

for( std::string line; getline( Filetwo, line ); )
{
y[l]=atof(line.c_str());
std::cout << y[l] <<"\n";

l++;
}
Filetwo.close();

   //Create the fitting function
   
   gr = new TGraph(n, x, y);
   gr->SetLineColor(2);
   gr->SetLineWidth(3);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(5);
   gr->SetTitle("Days with average temperature bellow 0 each year");
   gr->GetXaxis()->SetTitle("Year");
   gr->GetYaxis()->SetTitle("Nummber of days");
   gr->Draw("ACP");
   gr->Fit("pol1");
   TF1 *f3 = gr->GetFunction("pol1");
   f3->SetLineWidth(4);
   f3->SetLineColor(4);
   c1->Update();   
   c1->GetFrame()->SetFillColor(0);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
   c1->SaveAs("Lulea.pdf");
}
