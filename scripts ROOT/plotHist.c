void plotHist() { 
	// Para cargar en ROOT escribir: .x plotHist.c
	// Abrir archivo
	TFile *f = new TFile("ZtautauB_221.root"); //ZtautauB_221.root es proceso de background
	// Listar elementos del archivo
	f->GetListOfKeys()->Print(); // También se puede usar .ls
	// Seleccionar uno de los trees del archivo, por ejemplo "Nominal" (no tiene varianzas sistemáticas)
	TTree *t = (TTree*)f->Get("Nominal");
	// Ver las branches del tree
	t->Print();
	// Para graficar sólo una columna de la branch
	//t->Draw("MTW_Clos");
	// Declaración del reader del tree
	TTreeReader r(t);
	// Para acceder a la branch "Tau2Pt" del tree, usaremos br
	TTreeReaderValue<Float_t> br(r, "Tau2Pt"); //Tau2Pt es la variable
	// Histograma que se llenará con los elementos de la columna elegida de la branch
	TH1F *h = new TH1F("h1", "Tau2Pt", 100, 0, 160);
	// Recorre la branch completa
	while (r.Next()) {
      h->Fill(*br); // Puede ser llenado con más de una columna, por ejemplo *br1+*br2
    }
    // Color del histograma
    h->SetLineColor(kRed);
    // Graficar histograma
	/*h->Draw();*/
	// Lo mismo para la variable "Tau2Pt" del proceso ZtautauC_221.
	TFile *f2 = new TFile("ZtautauC_221.root");
	TTree *t2 = (TTree*)f2->Get("Nominal");
	TTreeReader r2(t2);
	TTreeReaderValue<Float_t> br2(r2, "Tau2Pt");
	TH1F *h2 = new TH1F("h2", "Tau2Pt", 100, 0, 160);
	while (r2.Next()) {
      h2->Fill(*br2); // Puede ser llenado con más de una columna, por ejemplo *br1+*br2
    }
    h2->SetLineColor(kBlue);
	// Graficar la misma variable (del TTree Nominal) para los procesos de background
	THStack *hs = new THStack("hs","Tau2Pt");
	hs->Add(h);
	hs->Add(h2);
	hs->Draw();
}
