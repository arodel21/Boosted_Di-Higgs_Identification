void bdt(){

TMVA::Tools::Instance();

// Reading signal file
TFile *signalFile = TFile::Open("new_s.root");
TTree *signalTree = (TTree*)signalFile->Get("Nominal");

// Reading bacground file
TFile *backgroundFile = TFile::Open("new_b.root");
TTree *backgroundTree = (TTree*)backgroundFile->Get("Nominal");

// Printing
signalTree->Print();
backgroundTree->Print();


// Creating structure of the classifier
TFile* outputFile = TFile::Open("Higgs_ClassificationOutput.root", "RECREATE");
TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,"!V:ROC:!Silent:Color:DrawProgressBar:AnalysisType=Classification");


TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");


dataloader->AddVariable("m_FJpt");
dataloader->AddVariable("m_FJm");
dataloader->AddVariable("m_DTpt");
dataloader->AddVariable("m_DTm");
dataloader->AddVariable("m_dPhiFTwDT");
dataloader->AddVariable("m_dRFJwDT");
dataloader->AddVariable("m_dPhiDTwMET");
dataloader->AddVariable("m_MET");
dataloader->AddVariable("m_hhm");
dataloader->AddVariable("m_bbttpt");


Double_t signalWeight = 1.0, backgroundWeight = 1.0;

dataloader->AddSignalTree(signalTree,   signalWeight );
dataloader->AddBackgroundTree (backgroundTree, backgroundWeight );


TCut mycuts="";
TCut mycutb="";

dataloader->PrepareTrainingAndTestTree(mycuts, mycutb,"nTrain_Signal=1000:nTrain_Background=2000:SplitMode=Random:NormMode=NumEvents:!V" );


factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT","!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=1:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );


factory->TrainAllMethods();

factory->TestAllMethods();

factory->EvaluateAllMethods();

auto c1  = factory->GetROCCurve(dataloader);
c1->Draw();

outputFile->Close();

if(!gROOT->IsBatch()) TMVA::TMVAGui("Higgs_ClassificationOutput.root");

///////////////////////
//Reader Stage
/////////////////////
TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

Float_t var1, var2, var3, var4,var5,var6,var7,var8, var9, var10, spec1;

reader->AddVariable("m_FJpt", &var1);
reader->AddVariable("m_FJm", &var2);
reader->AddVariable("m_DTpt", &var3);
reader->AddVariable("m_DTm", &var4);
reader->AddVariable("m_dPhiFTwDT", &var5);
reader->AddVariable("m_dRFJwDT", &var6);
reader->AddVariable("m_dPhiDTwMET", &var7);
reader->AddVariable("m_MET", &var8);
reader->AddVariable("m_hhm", &var9);
reader->AddVariable("m_bbttpt", &var10);

reader->BookMVA( "BDT", "dataset/weights/TMVAClassification_BDT.weights.xml" );


// Data file
TFile *input = TFile::Open( "new_b.root" );
TTree *myDataTree = (TTree*)input->Get("Nominal");


// New file with results
TFile *target = new TFile("realDataOutput.root","RECREATE" );
TTree *treeTarget = new TTree("tree","treelibrated tree");

Float_t vari1, vari2, vari3, vari4,vari5,vari6,vari7,vari8, vari9, vari10, speci1;


myDataTree->SetBranchAddress("m_FJpt", &vari1);
myDataTree->SetBranchAddress("m_FJpt", &vari2);
myDataTree->SetBranchAddress("m_DTpt", &vari3);
myDataTree->SetBranchAddress("m_DTm", &vari4);
myDataTree->SetBranchAddress("m_dPhiFTwDT", &vari5);
myDataTree->SetBranchAddress("m_dRFJwDT", &vari6);
myDataTree->SetBranchAddress("m_dPhiDTwMET", &vari7);
myDataTree->SetBranchAddress("m_MET", &vari8);
myDataTree->SetBranchAddress("m_hhm", &vari9);
myDataTree->SetBranchAddress("m_bbttpt", &vari10);


Float_t BDT_response, varBDT2;
treeTarget->Branch("BDT_response",&BDT_response);
treeTarget->Branch("var2",&varBDT2);

Float_t meanMvaData = 0;
UInt_t numEvents = 10;

for(UInt_t i=0; i<numEvents; i++){
	myDataTree->GetEntry(i);
	//meanMvaData += reader->EvaluateMVA("BDT");
	BDT_response = reader->EvaluateMVA("BDT");
	varBDT2 = 0.35;
	std::cout << "bdt_r" << BDT_response << std::endl;
	treeTarget->Fill();
    }
treeTarget->Write();

meanMvaData = meanMvaData/float(numEvents);
std::cout << "Mean response on data is " << meanMvaData  << "." << std::endl;
}
