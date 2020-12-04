
#include "SimpleAnomalyDetector.h"
#include <iostream>
#include <algorithm>

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief 
 * Check for every fearture1, by pearson who is the most corrolate
 * to him, and update vector<correlatedFeatures> that keep 
 * inside him astruct with feature1 that checked and feature 2 that corrolate.
 * @param ts 
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts){
	TimeSeries t = ts;
	float tempF1[t.getVector().at(0).second.size()] ;
	float tempF2[t.getVector().at(0).second.size()];
	correlatedFeatures Cpair;
	int itr = t.getVector().size();
	int N = sizeof(tempF1)/sizeof(tempF1[1]); //size of table's columns //cout<<t.getVector().at(i).first<<",  "<<t.getVector().at(j).first<<endl<<tempF1[1]<<"  "<<tempF2[1]<<endl;
	while (itr != 0){ 
		for(int i=0; i<t.getVector().size(); i++){
			float maxC = 0; 
			for(int j=0; j<t.getVector().size(); j++){
				if(t.getVector().at(i).first == t.getVector().at(j).first){
					continue;
				}
				for(int k=0; k<t.getVector().at(i).second.size(); k++){ //turn vector to float
					tempF1[k] = t.getVector().at(i).second[k];
					tempF2[k] = t.getVector().at(j).second[k];
				}
				if(maxC < pearson(tempF1,tempF2,N)){
					maxC = pearson(tempF1, tempF2, N);
					Cpair.corrlation = maxC;
					Cpair.feature1 = t.getVector().at(i).first;
					Cpair.feature2 = t.getVector().at(j).first;
					//create points array to lin_reg
					Point* ps[N];
					for(int t=0;t<N;t++){
						ps[t]=new Point(tempF1[t],tempF2[t]); //point (x,y)
					}Line l = linear_reg(ps,N);
					Cpair.lin_reg = l;
					//initilaie the threshold to be maximum dev * 1.1
					float maxDev = 0;
					for(int s=0; s<N; s++){
						if (maxDev < dev(*(ps[s]),l)){
							maxDev = dev(*(ps[s]),l);
						}		
					Cpair.threshold = maxDev*1.1;
					}
				}
			}
			cf.push_back(Cpair);
			itr--;
		}
	}
	// erase duplicates in corrolateFeature vector
	for(int n=0; n<cf.size(); n++){
		for(int m=1; m<cf.size()-1; m++){
			if ((cf.at(n).feature1 == cf.at(m).feature2) && (cf.at(n).feature2 == cf.at(m).feature1)){
				cf.erase(cf.begin()+m);
			}
		}
	}
	//Checker:
	for(correlatedFeatures cl: cf){
		cout<<cl.feature1<<"  "<<cl.feature2<<endl;
	}
}




/**
 * @brief on every report we want to return description and timestep.
 * 
 * @param ts 
 * @return vector<AnomalyReport> 
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
	vector<AnomalyReport> report;
	return report;

}

