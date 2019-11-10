{//Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   
   TCanvas *c1 = new TCanvas("c1","The nummber of winte days in Lulea over the years",200,10,700,500);

   c1->SetFillColor(42);
   c1->SetGrid();


Double_t x[n], y[n];


std::ifstream Fileone("/home/courseuser/MNXB01-project/CleanData/datasets/smhi-opendata_Lulea/data_years_smhi-opendata_Lulea.txt".c_str());
if(!Fileone){
		std::cout << "Not in file \n";
		return 1;

}
k=0
for( std::string line; getline( Fileone, line ); )
{
double ss = atof(line.c_str());
x[k]=ss
k++
}

std::ifstream Filetwo("/home/courseuser/MNXB01-project/CleanData/datasets/smhi-opendata_Lulea/Final.txt".c_str());
if(!Filetwo){
		std::cout << "Not in file \n";
		return 1;

}
k=0
for( std::string line; getline( Filetwo, line ); )
{
double ss = atof(line.c_str());
Y[k]=ss
k++
}

   gr = new TGraph(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("a simple graph");
   gr->GetXaxis()->SetTitle("X title");
   gr->GetYaxis()->SetTitle("Y title");
   gr->Draw("ACP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
