
//Starting on 5 May 2026;

#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

map<string,int> cmdMap={
    {"PRINT",1}
};

int print_Sequence(string src, int index);

void parse(string src)
{
  int i=0,l=src.length();

  while(i<l && (src[i]==' ' || src[i]=='\n'))
  {
    i++;
  }
  string s;

  while(i<l)
  {
    char ch= src[i];
    if(!s.empty() && (ch==' '|| ch=='\n'|| ch=='(' || ch==')'))
    {
      switch(cmdMap[s])
      {
        case 1:
          i=print_Sequence(src,i);
          //should return an index as well;
          s=""; ch=' ';
          break;
        default:
          cout<<"Token encountered: "<<s<<endl;
          cout<<"Error:Only print statements allowed!\n";
          return;
          break;
      }
    }
    if(ch!=' ' && ch!='\n')
    {
      s=s+ch;
    }
    i++;
  }
}

int print_Sequence(string src, int i)
{
  int l=src.length();
  char ch= src[i];
  while(i<l && (ch==' '||ch=='\n'))
  {
    i++; ch=src[i];
  }
  if(ch!='(')
  {
    cout<<"Error: Missing ( after PRINT\n";
    return l;
  }
  i++; ch=src[i];
  while(i<l && (ch==' '||ch=='\n'))
  {
    i++; ch=src[i];
  }
  if(ch!='"')
  {
    cout<<"Error:Missing "" in PRINT\n";
    return l;
  }
  string output;
  i++; ch=src[i];
  while(i<l && ch!='"')
  {
    output=output+ch;
    i++; ch=src[i];
  }
  if(ch!='"')
  {
    cout<<"Error:Missing closing ""\n";
    return l;
  }
  i++; ch=src[i];
  while(i<l && (ch==' '||ch=='\n'))
  {
    i++; ch=src[i];
  }
  if(ch!=')')
  {
    cout<<"Error: Missing closing )\n";
    return l;
  }
  cout<<output<<endl;
  return i;
}

int main(int argc, char* argv[])
{
  if(argc<2)
  {
    cout<<"Usage:"<<argv[0]<<" <sourcefile>\n";
    return 1;
  }

  string filename= argv[1];

  ifstream file(filename);
  string sourcecode= string(
      istreambuf_iterator<char>(file),
      istreambuf_iterator<char>()
  );

  parse(sourcecode);

  //cout<<sourcecode<<endl;

  return 0;
}
