# Machine learning-based algorithm for the identification of the boosted di-Higgs in ATLAS experiment events.
## Author: Andrea Rodríguez, Raquel Pezoa, Edson Carquín

This paper describes the development of machine learning-based algorithms for classifying signals and background events on a simulated dataset of the ATLAS experiment at CERN. More precisely, this work aims to identify the generation of a boosted di-Higgs decaying in two bottom quarks and two \emph{tau} leptons.

Four main configurations were designed for building the binary classifiers, using boosted decision trees and deep neural networks approaches. The grid search technique was performed for optimal parameter selection. Finally, the best models were selected based on the ROC AUC metric for each machine learning approach and configuration. The experiments showed that the best performance was achieved using the boosted decision tree approach, reaching $96\%$ of ROC AUC and $85\%$ of the F1 score.
