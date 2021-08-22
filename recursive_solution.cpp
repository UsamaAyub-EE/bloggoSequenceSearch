#include<iostream>
#include<vector>
#include<cctype>
#include<cstring>
#include<bits/stdc++.h>
using namespace std;
class bloggoSequenceSearch{
	public:
		void find_paths(int i,int j,int start,vector<vector<int>> indices,vector<vector<int>>& result)
		{
			if((i+1)==indices.size()-1)
			{
				for(auto a=0;a<indices[i+1].size();++a)
				{
					if(indices[i+1][a]>indices[i][j])
					{
						result.push_back({start,indices[i+1][a]});
					}
				}
			}
			else
			{
				for(auto a=0;a<indices[i+1].size();++a)
				{
					if(indices[i+1][a]>indices[i][j])
					{
						find_paths(i+1,a,start,indices,result);
					}
				}
			}
		}
		vector<int> Find_Key(string text,string key)
		{
			int H_key=0;
			int i;
			auto size=key.size();
			for(i=0;i<size;++i)
			{
				H_key+=tolower(key[i]);
			}
			auto text_size=text.size();
			int H_sliding_window=0;
			for(i=0;i<size;++i)
			{
				H_sliding_window+=tolower(text[i]);
			}
			int start=0,end=size-1;
			vector<int> indices;
			indices.clear();
			while(1)
			{
				if(H_sliding_window==H_key)
				{
					int m,n=start;
					for(m=0;m<size;++m,++n)
					{
						if(tolower(text[n])!=tolower(key[m]))
							break;
					}
					if(m==size)
					{
						if(tolower(text[n])<'a' || tolower(text[n])>'z')
							indices.push_back(start);
					}
					if(end==(text_size-1))
					{
						return indices;
					}
					H_sliding_window=H_sliding_window + tolower(text[end+1]) - tolower(text[start]);
					++end;
					++start;
				}
				else
				{
					if(end==(text_size-1))
					{
						return indices;
					}
					H_sliding_window=H_sliding_window + tolower(text[end+1]) - tolower(text[start]);
					++end;
					++start;
				}
			}
		}
		vector <string> findPassages(vector <string> documents, string query)
		{
			string temp;
			vector <string> q_words;
			for(auto i=0;i<query.size();++i)
			{
				if(query[i]=='.')
				{
					q_words.push_back(temp);
					i+=2;
					temp.clear();
				}
				else
				{
					temp.push_back(query[i]);
				}
			}
			q_words.push_back(temp);
			vector<string> result;
			for(auto i=0;i<documents.size();++i)
			{
				vector<vector<int>> indices;
				auto j=0;
				for(j=0;j<q_words.size();++j)
				{
					auto index=Find_Key(documents[i],q_words[j]);
					if(!index.empty())
						indices.push_back(index);
					else
						break;
				}
				if(j==q_words.size())
				{
					vector<vector<int>> indexes;
					for(auto b=0;b<indices[0].size();++b)
					{
						find_paths(0,b,indices[0][b],indices,indexes);
					}
					for(auto p=0;p<indexes.size();++p)
					{
						auto start=indexes[p][0];
						auto len=indexes[p][1]+q_words[j-1].size()-start;
						auto temp=to_string(i)+" "+to_string(start)+"["+documents[i].substr(start,len)+"]";
						result.push_back(temp);
					}
				}
			}
			return result;
		}
};
int main()
{
	bloggoSequenceSearch obj;
	vector <string> documents={"But in a larger sense we can not dedicate --", "we can not consecrate -- we can not hallow this", "ground. The brave men, living and dead, who", "struggled, here, have consecrated it far above", "our poor power to add or detract. The world will", "little note, nor long remember, what we say here,", "but can never forget what they did here. It is", "for us, the living, rather to be dedicated here", "to the unfinished work which they have, thus", "far, so nobly carried on. It is rather for us", "to be here dedicated to the great task remaining", "before us -- that from these honored dead we take", "increased devotion to that cause for which they", "here gave the last full measure of devotion --", "that we here highly resolve that these dead", "shall not have died in vain; that this nation", "shall have a new birth of freedom; and that", "this government of the people, by the people,", "for the people, shall not perish from the earth."};
	string query="the...People";
	vector <string> out=obj.findPassages(documents,query);
	for(auto i=0;i<out.size();++i)
		cout<<out[i]<<endl;
	return 0;
}
