double* McYield(string condition)
{
    TFile *file0    = TFile::Open("DATA/TrackerMuon/T&P_UPSILON_DATA.root");
    TTree *DataTree = (TTree*)file0->Get(("UPSILON_DATA"));
    
    //tenho de variar os valores deste corte para diferentes cortes em Pt
    double _mmin = 9.1;  double _mmax = 10.6;
    //double _mmin = 8.5;  double _mmax = 11;
    
    RooRealVar PassingProbeTrackerMuon("PassingProbeTrackerMuon", "PassingProbeTrackerMuon", 0, 1);
    
    RooRealVar InvariantMass("InvariantMass", "InvariantMass", _mmin, _mmax);
    RooRealVar ProbeMuon_Pt("ProbeMuon_Pt", "ProbeMuon_Pt", 0, 60);
    RooRealVar ProbeMuon_Eta("ProbeMuon_Eta", "ProbeMuon_Eta", -3, 3);
    RooRealVar ProbeMuon_Phi("ProbeMuon_Phi", "ProbeMuon_Phi", -3.5, 3.5);
    
    RooFormulaVar* redeuce = new RooFormulaVar("PPTM", condition.c_str(), RooArgList(ProbeMuon_Phi));
    RooDataSet *Data_ALL    = new RooDataSet("DATA", "DATA", DataTree, RooArgSet(InvariantMass, PassingProbeTrackerMuon, ProbeMuon_Phi),*redeuce);
    RooFormulaVar* cutvar = new RooFormulaVar("PPTM", strcat(condition.c_str(), "&& PassingProbeTrackerMuon == 1"), RooArgList(PassingProbeTrackerMuon, ProbeMuon_Phi));
    RooDataSet *Data_PASSING = new RooDataSet("DATA_PASS", "DATA_PASS", DataTree, RooArgSet(InvariantMass, PassingProbeTrackerMuon, ProbeMuon_Phi), *cutvar);//
    
    
    double* output = new double[2];
    output[0] = Data_ALL->sumEntries();
    output[1] = Data_PASSING->sumEntries();
    return output;
}
