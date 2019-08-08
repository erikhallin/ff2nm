#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
    //converts ffmaker outputfile to nmunits instad of A
    cout<<"ff2nm - 1.0 - convert units of a ffmaker file\n\n";

    cout<<"Name of file: ";
    vector<string> vec_header_lines;
    string filename,line,word;
    getline(cin,filename);
    ifstream infile(filename.c_str());
    if(infile==0)
    {
        cout<<"ERROR: Could not find that file\n";
        return 1;
    }
    if((int)filename.size()<5)
    {
        cout<<"ERROR: Filename too short\n";
        return 2;
    }

    //get data
    vector<float> vec_point_x;
    vector<float> vec_point_y;
    while(getline(infile,line))
    {
        //space line has data
        if(line[0]==' ')
        {
            stringstream ss(line);
            ss>>word;
            vec_point_x.push_back(atof(word.c_str()));
            ss>>word;
            vec_point_y.push_back(atof(word.c_str()));

            //cout<<std::scientific<<vec_point_x.back()<<", "<<vec_point_y.back()<<endl;
        }
        else
        {
            //header line
            vec_header_lines.push_back(line);
        }
    }
    infile.close();

    //data manipulation
    if(true)//A to nm
    {
        for(int i=0;i<(int)vec_point_x.size();i++)
        {
            vec_point_x[i]=vec_point_x[i]*=10;
        }
    }
    if(false)//I to log(I)
    {
        for(int i=0;i<(int)vec_point_y.size();i++)
        {
            vec_point_y[i]=log10(vec_point_y[i]);
        }
    }

    //print new file
    filename.append(1,'x');
    filename[(int)filename.size()-1]=filename[(int)filename.size()-2];
    filename[(int)filename.size()-2]=filename[(int)filename.size()-3];
    filename[(int)filename.size()-3]=filename[(int)filename.size()-4];
    filename[(int)filename.size()-4]=filename[(int)filename.size()-5];
    filename[(int)filename.size()-5]='_';
    ofstream outfile(filename.c_str());
    if(outfile==0)
    {
        cout<<"ERROR: Could not make out-file\n";
        return 3;
    }
    for(int i=0;i<(int)vec_header_lines.size();i++)
    {
        outfile<<vec_header_lines[i]<<endl;
    }
    for(int i=0;i<(int)vec_point_x.size() && i<(int)vec_point_y.size();i++)
    {
        outfile<<" "<<std::scientific<<vec_point_x[i]<<"  "<<std::scientific<<vec_point_y[i]<<endl;
    }
    outfile.close();

    cout<<"Complete\n\n";


    return 0;
}
