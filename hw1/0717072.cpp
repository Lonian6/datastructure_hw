#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) 
{ 
    ifstream file(argv[1]);
    string str;
    int num[2];			// d1, d2 size
    int index = 0;
    int line_num = 0;
    int arr_index = 0;
    double t;
    double **a = new double *[2];	// d1, d2 value
    
    // get 2 array d1, d2
    while (getline(file, str))
    {
        // Process str
        //cout << str << endl;
        num[line_num] = count(str.begin(), str.end(), ' ')+1;
	//cout << num[line_num] << endl;
	a[line_num] = new double[num[line_num]];
	
	istringstream iss;
    	iss.str(str);
	arr_index = 0;
    	while(iss>>t) {
            //cout<<t<<endl;
	    a[line_num][arr_index] = t;
	    arr_index++;
    	}

	line_num++;
    }
    file.close();
    /*for(int i1=0; i1<2; i1++){
        for(int i2=0; i2<num[i1]; i2++){
	    cout << a[i1][i2] << ' ';
	}
	cout << endl;
    }*/
    
    // process d1/d2 = q ... r
    int q_num = num[0]-num[1]+1;
    //cout << "q_num = " << q_num << endl;
	//declare q, r array
    double q[q_num];

    //cout << "============COUNTING=============" << endl;
    int r_num = 0;
    for (int i3=0; i3<q_num; i3++){
        q[i3] = a[0][i3] / a[1][0];
	for (int i4=0; i4<num[1]; i4++){
	    a[0][i3+i4] = a[0][i3+i4]-q[i3]*a[1][i4];
	    //cout << a[0][i3+i4] << " ";
	    if (i3 == q_num-1){
		if (a[0][i3+i4] != 0) r_num++;
	    }
	}
	//cout << endl;
	//cout << "q " << q[i3] << endl;
    }
    //cout << "r_num = " << r_num << endl;
    //cout << "============Show Q=============" << endl;
    for (int i5=0; i5<q_num; i5++){
	cout << q[i5] << " ";
    }
    cout << endl;

    /*int r_num = 0;
    for (int i6=0; i6<num[0]; i6++){
	//cout << a[0][i6] << " ";
	if (a[0][i6] != 0) r_num++;
    }*/
    //cout << "============Show R=============" << endl;
    double r[r_num];
    for (int i7=0; i7<r_num; i7++){
	r[i7] = a[0][num[0]-r_num+i7];
	cout << r[i7] << " ";
    }
    cout << endl;
    

    // save q, r to output file
    ofstream ofs;
    ofs.open(argv[2]);
    //cout << argv[2] << endl;
    if (!ofs.is_open()) {
        cout << "Failed to open file.\n";
    }
    else {
        for (int i = 0; i < q_num; i++) {
            if (i == q_num-1){
                ofs << q[i] << endl;
            }
            else ofs << q[i] << ' ';
        }
        for (int i = 0; i < r_num; i++) {
            if (i == r_num-1){
                ofs << r[i];
            }
            else ofs << r[i] << ' ';
        }
        ofs.close();
    }
    return 0;
}
