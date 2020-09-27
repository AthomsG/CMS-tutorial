TEfficiency* get_efficiency(TH1F* ALL, TH1F* PASS)
{
    TFile* pFile = new TFile("Efficiency_Run2011.root","recreate");
    TEfficiency* pEff = new TEfficiency();
    pEff->SetName("Efficiency");
    pEff->SetPassedHistogram(*PASS, "f");
    pEff->SetTotalHistogram (*ALL,"f");
    
    pEff->SetDirectory(gDirectory);
    pFile->Write();
    
    TCanvas* oi = new TCanvas();
    oi->cd();
    pEff->Draw();
    
    gPad->Update();

    auto graph = pEff->GetPaintedGraph();
    graph->SetMinimum(0.8);
    graph->SetMaximum(1.2);
    gPad->Update();
    
    return pEff;
}
