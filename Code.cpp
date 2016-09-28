
#include <iostream>
#include <string>
#include <fstream>
#include <vector> 

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>


using namespace std;

struct PersonalDetail
{
   string firsName;
   string secondName;
   int  score;
   
   PersonalDetail(string firstName,string secondName,int score);
   PersonalDetail( const PersonalDetail &personalDt);
   PersonalDetail ()
   {
	   firsName="";
	   secondName="";
	   score=0;
   };
   friend bool operator <(const PersonalDetail &op1,const PersonalDetail &op2);
   
};

    PersonalDetail::PersonalDetail( const PersonalDetail &personalDt)
	 {
		 firsName=personalDt.firsName;
		 secondName=personalDt.secondName;
		 score=personalDt.score;
	 }

    PersonalDetail::PersonalDetail(string firstName,string secondName,int score)
    {
	   this->firsName= firstName;
	   this->secondName=secondName;
	   this->score=score;
    }

 

   
bool operator <(const PersonalDetail &operand1,const PersonalDetail &operand2)
   {
	   bool retValue=false;
	   if(operand1.score==operand2.score)
	   {
		   if(operand1.firsName.compare(operand2.firsName)<0)
		   {
		      retValue= true;
	       }else
	       {
		      retValue= false;
	       }
	   }else if(operand1.score<operand2.score)
	   {
		   retValue= operand1.score<operand2.score;
	   }
       
       return retValue;
   }
 

 struct Sorter
{
    bool operator()( const PersonalDetail& operand1, const PersonalDetail& operand2 ) const 
	{
    	bool retValue=true;
	   if(operand1.score==operand2.score)
	   {
		   if(operand1.firsName.compare(operand2.firsName)>0)
		   {
		      retValue= false;
	       }else
	       {
		      retValue= true;
	       }
	   }else if(operand1.score<operand2.score)
	   {
		   retValue= operand1.score>operand2.score;
	   }
       
       return retValue;
    }
};
 

static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}


static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}


static inline void trim(std::string &s)
 {
    ltrim(s);
    rtrim(s);
}

static inline std::string ltrimmed(std::string s)
 {
    ltrim(s);
    return s;
}

static inline std::string rtrimmed(std::string s) 
{
    rtrim(s);
    return s;
}

static inline std::string trimmed(std::string s) 
{
    trim(s);
    return s;
}

void split(const string &s, char delim, vector<string> &elems)
 {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
}


vector<string> split(const string &s, char delim) 
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}


  
void  TrimString( vector<string> &vectorStrings,vector<string> &trimmedString )
{

    vector<string>::iterator it = vectorStrings.begin();
    trimmedString.clear();
    while( it != vectorStrings.end()) 
    {
       string tempString=trimmed(*it);
       trimmedString.push_back(tempString);
       it++;
    }
}
  
 std::string Remove_extension(const string& filename)
 {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) {
		return filename;
	}
    return filename.substr(0, lastdot); 
}  
   
   
   
 int ReadRecodrds(string fileName,std::vector<PersonalDetail> &records)
 {
    int retValue=0;
    ifstream inputfile;
    int recordCount=0;
    int recordParsed=0;
    
    inputfile.open(fileName.c_str()); 
    if(inputfile.is_open()){
       while (!inputfile.eof())
       { 
           string tempValue;
           getline(inputfile,tempValue); 
           recordCount++;
           vector<string> spliteString=split(tempValue,',');
           if(spliteString.size()<3)
		   {
              if(spliteString.size()>1)
              { 
                cout<<"Record is incorrect -->"<<tempValue<<"\n";
              }
              continue;
           }

           recordParsed++; 
           vector<string>strippedString;
           TrimString(spliteString,strippedString);
           //cout<<spliteString.size();
           string scoreString=strippedString[2];
		   
		   int isNumber=true;
		   for(string::const_iterator k = scoreString.begin(); k != scoreString.end(); ++k){
		      isNumber &= isdigit(*k);
		   }
		   if(isNumber==false){
			   cout<<"Record should be numeric  at -->"<<tempValue<<tempValue<<"\n";
		   }
           int scores=atoi(scoreString.c_str());
           PersonalDetail personRecord =PersonalDetail(strippedString[0],strippedString[1],scores); 	  
           records.push_back(personRecord);
        }
		inputfile.close();
	    
		cout<<"Recod Total="<<recordCount-1 <<"Record Parsed="<<recordParsed<<"\n";
		
	}else
	{
		cout<<"File Could not opened ->"<<fileName<<"\n";
		retValue =-1;
	} 
	return retValue;
 }
   
   
 int WriteRecords(string fileName,const std::vector<PersonalDetail> &records)  
 {
	 int retValue=-1;
	 ofstream outputFile ( fileName.c_str());
	 if(outputFile.is_open())
	 {
		for(int i=0;i<records.size();i++)
		{
			PersonalDetail tmpDt=records[i];
		  	outputFile<<tmpDt.firsName<<","<< tmpDt.secondName<<","<<tmpDt.score<<"\n"; 
		} 
		
		retValue=0;
		outputFile.close(); 
	 }
	 
	 return retValue;
 }
  

int main(int argc,char *argv[])
{
	string fileName="names.txt";
	int retValue=0;
	
    if(argc>=2)
	{
		fileName=string(argv[1]);
		
	}

    string outputFile=Remove_extension(fileName); 
	outputFile=outputFile+"-graded.txt";	
	
	vector<PersonalDetail>  personalDt;
	if(ReadRecodrds(fileName,personalDt)==0)
	{
		if(personalDt.size()>0)
		{
			//std::sort (personalDt.begin(), personalDt.end());//Ascending order
			std::sort (personalDt.begin(), personalDt.end(),Sorter()); 
		}	
		
		if(WriteRecords(outputFile,personalDt) !=0)
		{
			retValue=1;
		}
	}else
	{
		retValue=2;
	}	
	
	
	
	
	return 0;
}
   
   