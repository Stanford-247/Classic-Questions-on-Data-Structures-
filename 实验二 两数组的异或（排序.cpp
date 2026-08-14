"""
已知两个线性表，求两个线性表的异或结果
"""
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	vector <int> La;
	vector <int> Lb;
	vector <int> Lc;
	int t = -1;
	while(t != 0)
	{
		cin>>t;
		La.push_back( t );
	}
	cin >> t;//��0 
	t = -1;//����
	while(t != 0)
	{
		cin >> t;
		Lb.push_back( t );
	} 
	cin >> t;
	//���� 
	sort(La.begin(), La.end());
	sort(Lb.begin(), Lb.end());
	int i = 0, j = 0;
	while(i < La.size() && j < Lb.size())
	{
		if(La[i] == Lb[j])
		{
			i++;
			j++;
		}//�������ж��У�����
		else if(La[i] > Lb[j])
		{
			j++;
			Lc.push_back(Lb[j]);
		}//��ʱLb[j]�϶�����La��Lb��
		else if(La[i] < Lb[j])
		{
			i++;
			Lc.push_back(La[i]);
		} 
	}
	//��ʣ�ಿ�ֲ��� 
	if(La.empty())
		Lc.insert(Lc.end(), Lb.begin() + j, Lb.end());
	if(Lb.empty())
		Lc.insert(Lc.end(), La.begin() + i, La.end());
	cout<<"�����������Ϊ�� "; 
	for(int num : Lc)
	{
		cout<< num << " ";
	}
	cout << endl;
	return 0; 
}
