//Guixu Li\ligui@oregonstate.edu\933948526
//Chih-hao, Feng\fengchi@oregonstate.edu\933956498
//Dept ◃▹Dept.managerid=Emp.eid Emp

#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm> 

using namespace std;
//2D array to store first csv

vector<vector<string> > first_Array;
vector<vector<string> > second_Array;
//vector<vector<string> > more_temp;
vector<vector<string> > vector_temp_f;
vector<vector<string> > vector_temp_s;
vector<vector<string> > vector_temp_f_merge;
vector<vector<string> > vector_temp_s_merge;
vector<vector<string> > result;
vector<int>  first_id;
vector<int> second_id;
string first_temp;
string second_temp;
int first_index;
int second_index;
// int start = 0;
// int stop = 0;
// int counter = 0;
int mm_block_size = 22;
//int real_size;
//int last_size;
// int array_mid;
// int left_best;
// int right_best;
// int left_new;
// int right_new;
// int mid_new;
// int boundary;
//check sort
int check_sort(vector<int> array, int length){
	for (int i = 0; i < length; i++)
	{
		if (array[i]>array[i+1])
		{
			return 0;
		}
	}
	return 1;
}
//sort method
vector<vector<string> > insertion(vector<vector<string> > array, int begin, int end, int index){
	for (int i = begin + 1; i <= end; i++)
	{
		for (int j = i - 1; j >= begin; j--)
		{
			if (atoi((array[j][index]).c_str()) > atoi((array[j+1][index]).c_str()))
			{
				vector<string> temp;

				temp.push_back(array[j][0]);
				temp.push_back(array[j][1]);
				temp.push_back(array[j][2]);
				temp.push_back(array[j][3]);

				array[j][0] = array[j+1][0];
				array[j][1] = array[j+1][1];
				array[j][2] = array[j+1][2];
				array[j][3] = array[j+1][3];

				array[j+1][0] = temp[0];
				array[j+1][1] = temp[1];
				array[j+1][2] = temp[2];
				array[j+1][3] = temp[3];
			}else{
				break;
			}
		}
	}
	return array;
}
//Two pass multi-way merge sort
vector<vector<string> > TPMMS(vector<vector<string> > array, int index){
	int real_size = 0;
	int start = 0;
	int stop = 0;
	int counter = 0;
	real_size = array.size()-1;
	vector<vector<string> > TPMMS_temp(array.size());
	vector<vector<string> > more_temp;
	if (real_size <= mm_block_size)
	{
		return insertion(array, 0, real_size, index);

	}else{
		if ((array.size())%mm_block_size == 0)
		{
			stop = stop + mm_block_size - 1;
			for (int i = 0; i < (array.size()/mm_block_size); i++)
			{
				// cout<<"loop is: "<<array.size()/mm_block_size<<endl;
				more_temp = insertion(array, start, stop, index);
				start += mm_block_size;
				stop += mm_block_size; 
				for (int j = counter; j < (counter+mm_block_size); j++)
				{
					for (int k = 0; k < 4; k++)
					{
						TPMMS_temp[j].push_back(more_temp[j][k]);
					}
				}counter += mm_block_size;
			}
		}
		else if ((array.size())%mm_block_size != 0)
		{
			stop = stop + mm_block_size - 1;
			for (int i = 0; i < (array.size()/mm_block_size); i++)
			{
				// cout<<"loop is: "<<array.size()/mm_block_size<<endl;
				more_temp = insertion(array, start, stop, index);
				start += mm_block_size;
				stop += mm_block_size; 
				for (int j = counter; j < (counter+mm_block_size); j++)
				{
					for (int k = 0; k < 4; k++)
					{
						TPMMS_temp[j].push_back(more_temp[j][k]);
					}
				}counter += mm_block_size;
			}
			// cout<<"counter = "<<counter<<endl;
			int last_size = 0;
			last_size = array.size()-((array.size()/mm_block_size)*mm_block_size);
			// cout<<"size = "<<array.size()<<endl;
			// cout<<"last_size"<<last_size<<endl;
			// cout<<"new stop 1 = "<<stop<<endl;
			stop = stop-mm_block_size+last_size;
			// cout<<"new start = "<<start<<endl;
			// cout<<"new stop = "<<stop<<endl;
			more_temp = insertion(array, start, stop, index);
			for (int x = counter; x < (counter+last_size); x++)
				{
					for (int y = 0; y < 4; y++)
					{
						TPMMS_temp[x].push_back(more_temp[x][y]);
					}
				}
		}
	}
	return TPMMS_temp;
}
//merge
vector<vector<string> > merge_basesort(vector<vector<string> > array, int index){
	
	if (array.size() < mm_block_size)
	{
		return array;
	}else if ((array.size()/mm_block_size) == 2 && (array.size()%mm_block_size) == 0)
	{
		int array_mid = (array.size())/2;
		int left_best = 0;
		int right_best = left_best + mm_block_size;
		vector<vector<string> >merge_temp_f_store(array.size());
		for (int i = 0; i < array.size(); i++)
		{
			if (left_best < array_mid && right_best <= (array.size()-1))
			{	
				if(atoi(array[left_best][index].c_str()) <= atoi(array[right_best][index].c_str()))
				{
					merge_temp_f_store[i].push_back(array[left_best][0]);
					merge_temp_f_store[i].push_back(array[left_best][1]);
					merge_temp_f_store[i].push_back(array[left_best][2]);
					merge_temp_f_store[i].push_back(array[left_best][3]);
					left_best++;
				}else{
					merge_temp_f_store[i].push_back(array[right_best][0]);
					merge_temp_f_store[i].push_back(array[right_best][1]);
					merge_temp_f_store[i].push_back(array[right_best][2]);
					merge_temp_f_store[i].push_back(array[right_best][3]);
					right_best++;
				}
			}else if (left_best < array_mid && right_best > (array.size()-1))
			{
				merge_temp_f_store[i].push_back(array[left_best][0]);
				merge_temp_f_store[i].push_back(array[left_best][1]);
				merge_temp_f_store[i].push_back(array[left_best][2]);
				merge_temp_f_store[i].push_back(array[left_best][3]);
				left_best++;
			}else if (left_best >= array_mid && right_best <= (array.size()-1))
			{
				merge_temp_f_store[i].push_back(array[right_best][0]);
				merge_temp_f_store[i].push_back(array[right_best][1]);
				merge_temp_f_store[i].push_back(array[right_best][2]);
				merge_temp_f_store[i].push_back(array[right_best][3]);
				right_best++;
			}
		}
	return merge_temp_f_store;
	}else
	{
		vector<vector<string> >merge_temp_storage(array.size());

		for (int j = 0; j < mm_block_size; j++)
		{
			merge_temp_storage[j].push_back(array[j][0]);
			merge_temp_storage[j].push_back(array[j][1]);
			merge_temp_storage[j].push_back(array[j][2]);
			merge_temp_storage[j].push_back(array[j][3]);
		}
		int looper = 0;
		if ((array.size()%mm_block_size) == 0)
		{
			looper = (array.size()/mm_block_size)-1;
		}else if ((array.size()/mm_block_size) != 0)
		{
			looper = (array.size()/mm_block_size);
		}
		for (int h = 0; h < looper; h++)
		{
			int left_new = 0;
			int right_new = mm_block_size * (h+1);
			int mid_new = mm_block_size * (h+1);
			int boundary = mm_block_size * (h+1) + mm_block_size - 1;
			if (boundary > (array.size()-1))
			{
				boundary = array.size()-1;
			}
			//cout<<"left:"<<left_new<<"mid:"<<mid_new<<"right"<<right_new<<"boundary"<<boundary<<endl;
			vector<vector<string> >inside_temp_storage(array.size());
			for (int k = 0; k < array.size(); k++)
			{
				if ((left_new < mid_new) && (right_new <= boundary))
				{
					if (atoi(merge_temp_storage[left_new][index].c_str()) < atoi(array[right_new][index].c_str()))
					{
						inside_temp_storage[k].push_back(merge_temp_storage[left_new][0]);
						inside_temp_storage[k].push_back(merge_temp_storage[left_new][1]);
						inside_temp_storage[k].push_back(merge_temp_storage[left_new][2]);
						inside_temp_storage[k].push_back(merge_temp_storage[left_new][3]);

						left_new++;
						//cout<<"实时第一层left状态"<<left_new<<endl;
					}else{
						inside_temp_storage[k].push_back(array[right_new][0]);
						inside_temp_storage[k].push_back(array[right_new][1]);
						inside_temp_storage[k].push_back(array[right_new][2]);
						inside_temp_storage[k].push_back(array[right_new][3]);

						right_new++;
						//cout<<"实时第一层right状态"<<right_new<<endl;
					}
				}else if ((left_new < mid_new) && (right_new > boundary))
				{
					inside_temp_storage[k].push_back(merge_temp_storage[left_new][0]);
					inside_temp_storage[k].push_back(merge_temp_storage[left_new][1]);
					inside_temp_storage[k].push_back(merge_temp_storage[left_new][2]);
					inside_temp_storage[k].push_back(merge_temp_storage[left_new][3]);

					left_new++;
					//cout<<"实时第二层left状态"<<left_new<<endl;
				}else if ((left_new >= mid_new) && (right_new <= boundary))
				{
					inside_temp_storage[k].push_back(array[right_new][0]);
					inside_temp_storage[k].push_back(array[right_new][1]);
					inside_temp_storage[k].push_back(array[right_new][2]);
					inside_temp_storage[k].push_back(array[right_new][3]);

					right_new++;
					//cout<<"实时第二层right状态"<<right_new<<endl;
				}
			}
			merge_temp_storage = inside_temp_storage;
		}
	return merge_temp_storage;
	}
	// else if ((array.size()%mm_block_size) != 0 && (array.size()/mm_block_size) >= 2)
	// {

	// }
}
//get min
int max_fun(int a,int b)
{
	if(a>b)
	{
		return a;
	}
	return b;
}
//join
vector<vector<string> > join_fun(vector<vector<string> >array_l, vector<vector<string> >array_r)
{
	//cout<<"here"<<endl;
	int index_l = 0;
	int index_r = 0;
	int tuple = 0;
	int max_new = max_fun(array_l.size(),array_r.size());
	vector<vector<string> > join_array(max_new);
	while(1)
	{
		if ((index_l >= array_l.size()) || (index_r >= array_r.size()))
		{
			break;
		}else
		{
		if (atoi(array_l[index_l][3].c_str()) == atoi(array_r[index_r][0].c_str()))
		{
			join_array[tuple].push_back(array_l[index_l][0]);
			join_array[tuple].push_back(array_l[index_l][1]);
			join_array[tuple].push_back(array_l[index_l][2]);
			join_array[tuple].push_back(array_l[index_l][3]);
			join_array[tuple].push_back(array_r[index_r][0]);
			join_array[tuple].push_back(array_r[index_r][1]);
			join_array[tuple].push_back(array_r[index_r][2]);
			join_array[tuple].push_back(array_r[index_r][3]);
			index_l++;
			tuple++;

		}else if (atoi(array_l[index_l][3].c_str()) < atoi(array_r[index_r][0].c_str()))
		{
			index_r++;

		}
		else if (atoi(array_r[index_r][0].c_str()) < atoi(array_l[index_l][3].c_str()))
		{
			index_r++;
		}
		}
	}
	return join_array;
}
int main(int argc, char const *argv[])
{
//-----------------------------get data from file start-----------------------------//
	ifstream inFile_f("Dept.csv",ios::in);
	string line_f;
	while(getline(inFile_f,line_f)) 
	{	
		//get string by line
		stringstream ss_f(line_f);
		string str_f;
		vector<string> line_Array_f;
		//get string by ","
		while(getline(ss_f,str_f,','))
		{
			line_Array_f.push_back(str_f);
		}
		first_Array.push_back(line_Array_f);
	}
	//get all manager_id in an array
	for (int i = 1; i < first_Array.size(); i++)
	{
		first_temp = first_Array[i][3];
		first_index = atoi(first_temp.c_str());
		first_id.push_back(first_index);
	}
	//Read File 2
	ifstream inFile_s("Emp.csv",ios::in);
	string line_s;
	while(getline(inFile_s,line_s)) 
	{	
		//get string by line
		stringstream ss_s(line_s);
		string str_s;
		vector<string> line_Array_s;
		//get string by ","
		while(getline(ss_s,str_s,','))
		{
			line_Array_s.push_back(str_s);
		}
		second_Array.push_back(line_Array_s);
	}
	//get all eid in an array
	for (int i = 1; i < second_Array.size(); i++)
	{
		second_temp = second_Array[i][0];
		second_index = atoi(second_temp.c_str());
		second_id.push_back(second_index);
	}
//-----------------------------get data from file finish-----------------------------//
	
	if (check_sort(first_id,first_id.size()) == 0)
	{
		cout<<"The input table is not sorted!"<<endl;
		vector_temp_f = TPMMS(first_Array,3);
		vector_temp_f_merge = merge_basesort(vector_temp_f,3);
	}else{
		cout<<"The input table is sorted!"<<endl;
	}

	if (check_sort(second_id,first_id.size()) == 0)
	{
		cout<<"The input table 2 is not sorted!"<<endl;
		vector_temp_s = TPMMS(second_Array,0);
		vector_temp_s_merge = merge_basesort(vector_temp_s,0);
	}else{
		cout<<"The input table 2 is sorted!"<<endl;
	}

	result = join_fun(vector_temp_f_merge,vector_temp_s_merge);
/////////////////////////////////////print area/////////////////////////////////////////
	// cout<<"first sort"<<endl;
	// cout<<"size = "<<vector_temp_f.size()<<endl;
	// for (int i = 0; i < vector_temp_f.size(); i++)
	// {
	// 	for (int j = 0; j < vector_temp_f[i].size(); j++)
	// 	{
	// 		cout<<vector_temp_f[i][j]<<" ";
	// 	}cout<<endl;
	// }
	// cout<<"first merge"<<endl;
	// cout<<"size = "<<vector_temp_f_merge.size()<<endl;
	// for (int i = 0; i < vector_temp_f_merge.size(); i++)
	// {
	// 	for (int j = 0; j < vector_temp_f_merge[i].size(); j++)
	// 	{
	// 		cout<<vector_temp_f_merge[i][j]<<" ";
	// 	}cout<<endl;
	// }
	// cout<<"second sort"<<endl;
	// cout<<"size = "<<vector_temp_s.size()<<endl;
	// for (int i = 0; i < vector_temp_s.size(); i++)
	// {
	// 	for (int j = 0; j < vector_temp_s[i].size(); j++)
	// 	{
	// 		cout<<vector_temp_s[i][j]<<" ";
	// 	}cout<<endl;
	// }
	// cout<<"second merge"<<endl;
	// cout<<"size = "<<vector_temp_s_merge.size()<<endl;
	// for (int i = 0; i < vector_temp_s_merge.size(); i++)
	// {
	// 	for (int j = 0; j < vector_temp_s_merge[i].size(); j++)
	// 	{
	// 		cout<<vector_temp_s_merge[i][j]<<" ";
	// 	}cout<<endl;
	// }
	// for (int i = 0; i < result.size(); i++)
	// {
	// 	for (int j = 0; j < result[i].size(); j++)
	// 	{
	// 		cout<<result[i][j]<<" ";
	// 	}cout<<endl;
	// }
/////////////////////////////////////print area/////////////////////////////////////////
	ofstream outFile;
	outFile.open("join.csv",ios::out);
	
	for (int i = 0; i < result.size(); i++)
	{
		for (int j = 0; j < result[i].size(); j++)
		{
			outFile<<result[i][j]<<",";
		}outFile<<endl;
	}
	cout<<"You successfully created the join.csv file!"<<endl;
	cout<<"This sort merge join table is made by Guixu Li & Chih-hao Feng"<<endl;
	return 0;
}