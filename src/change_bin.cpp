

void change_bin(string condition, string MuonId, string quantity, double* init_conditions, string hist_file = "Histograms.root")
{
    TFile *_file0 = TFile::Open(hist_file.c_str());
    
    TH1F *hist_all  = (TH1F*)_file0->Get("ALL");
    TH1F *hist_pass = (TH1F*)_file0->Get("PASS");

    int bin_iD = /*Bin where you want to redo the fit*/;
    
    double * values = new double[4];
    
    values = doFit(conditions[i], MuonId, quantity, init_conditions);
    
    hist_all->SetBinContent(bin_iD, values[0]);
    hist_all->SetBinError(bin_iD, values[2]);
    
    hist_pass->SetBinContent(bin_iD, values[1]);
    hist_pass->SetBinError(bin_iD, values[3]);
    
    TFile* EfficiencyFile = TFile::Open(hist_file.c_str(),"RECREATE");
    hist_all->SetDirectory(gDirectory);
    hist_pass->SetDirectory(gDirectory);
    EfficiencyFile->Write();
    
    get_efficiency(hist_all, hist_pass);
}
