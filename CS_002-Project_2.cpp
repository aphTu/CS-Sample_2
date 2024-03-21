#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const int SIZE = 36;

int menu();
void inputData(ifstream&, ifstream&, int[], string[], int[], int[]);
void menu_1(int [], string [], int[], int[]);
void menu_2(int [], string [], int [], int []);
void menu_3(int[], int[]);
void menu_4(int [], string[], int[], int[]);
void menu_5(ifstream&, ifstream&,int [], string [], int [], int []);
void sortCpp(int [], string [], int [], int []);
void sortJava(int [], string[], int[], int[]);

int main()
{
  //variable for the file name
  //storing what file the user want to open
  string file_name_1;
  string file_name_2;
  cout << "Enter fileName1: ";
  cin >> file_name_1;
  cout << "Enter fileName2: ";
  cin >> file_name_2;

  //variable for opening the file
  //storing the file path the user wanted to 
  ifstream infile_1;
  ifstream infile_2;


  infile_1.open(file_name_1);
  if(infile_1.fail())
  {
    cout << "File "<< file_name_1 <<" does not exist";
    exit(1);
  }
  infile_2.open(file_name_2);
  if (infile_2.fail())
  {
    cout << "File " << file_name_2 << " does not exist";
    exit(1);
  }
  int id[SIZE];
  string name[SIZE];
  int cpp[SIZE];
  int java[SIZE];
  

  int option = 0;
  while(option != 6)
  {
    inputData(infile_1,infile_2, id, name, cpp, java);
    option = menu();
    if(option == 6)
    {
      cout << "Exited the program";
      infile_1.close();
      infile_2.close();
    } else if(option == 1)
    {
      menu_1(id,name,cpp,java);
    } else if (option == 2)
    {
      menu_2(id,name,cpp,java);
    } else if (option== 3)
    {
      menu_3(cpp, java);
    } else if (option == 4)
    {
      menu_4(id, name, cpp,java);
    } else if (option == 5)
    {
      menu_5(infile_1, infile_2,id, name, cpp, java);
    }
  }
}

//The main menu function of the project
//return the chosen number the user has input
//number will be used to choose what option to open next
int menu(){
  cout << endl << "-------------------------------------------"<< endl;
  cout << setw(22) << "Menu" << endl;
  cout << "-------------------------------------------"<< endl;
  cout << setw(1) <<"1. Show the original data: " << endl;
  cout << setw(1) <<"2. Show data in ascending order of ID" << endl;
  cout << setw(1) <<"3. Show the average of each course" << endl;
  cout << setw(1) <<"4. Show C++ score in descendng order" << endl;
  cout << setw(1) <<"5. Show top three students of C++ and Java" << endl;
  cout << setw(1) << "6. Exit" << endl << endl;

  int chosen;
  cout << setw(1) << "Choose one menu (1~6): ";
  cin >> chosen;
  return chosen;
}

//take in the file 1 and file 2 to text file, id, name, c++, and java array
//use to fill the id, name, c++, and java array with data from the file
//no return value
void inputData(ifstream& inTheFile_1, ifstream& inTheFile_2, int id[], string name[], int cpp[], int java[])
{
    inTheFile_1.seekg(0, ios::beg);
    inTheFile_2.seekg(0, ios::beg);
    //putting data into array
    //will reset the array data after every menu usage
    int i = 0;
    while(!inTheFile_1.eof())
    {
    
      inTheFile_1 >> id[i] >> name[i];
      i++;
    }
    while(!inTheFile_2.eof())
    {
      int index;
      inTheFile_2>> index;
      //check to see newly add index from file 2 align with the first file 
      //and input the data asscociated with that file to that correct location
      //in the array
      for(int k = 0; k<SIZE; k++)
      {
        if(index == id[k])
        {
          inTheFile_2 >> cpp[k] >> java[k];
          break;
        }
      }
    } 
}

//take in the id, name, c++, and java array
//print out the original data of the file
//no return
void menu_1(int id[], string name[], int cpp[], int java[])
{
  cout << "***** Menu 1 Result *****" << endl
  <<"-------------------------" << endl;
  for(int i =0; i<SIZE; i++)
  {
    cout << setw(2) << id[i] << setw(10) << name[i]
    <<" " << cpp[i] << " " << java[i] << endl;
  }
  cout << endl;
}

//take in id, name, c++, and java array
//print out the id of the student, and name, c++ score, and java score that associate with that student in ascending order
//no return
void menu_2(int id[], string name[], int cpp[], int java[])
{
  for (int i = 0; i<SIZE; i++)
  {
    for(int j = 0; j< SIZE- 1; j++)
    {
      if(id[j] > id[i])
      {
        swap(id[j], id[i]);
        swap(name[j],name[i]);
        swap(cpp[j], cpp[i]);
        swap(java[j],java[i]);
      }
    }
  }
  cout << "***** Menu 2 Result *****" << endl
  <<"-------------------------" << endl; 
  for(int k = 0; k<SIZE; k++)
  {
    cout << setw(2) << id[k] << setw(10) << name[k]
    <<" " << cpp[k] << " " << java[k] << endl;
  }
  cout << endl;
  
}

//take in c++ and java array
//print out the average score of both c++ and java
//no return
void menu_3(int cpp[], int java[])
{
  cout << "***** Menu 3 Result *****" << endl
  <<"-------------------------" << endl; 
  double aveCpp = 0, aveJava = 0;
  int numOfData = 0;
  for(int i = 0; i<SIZE;i++)
  {
    aveCpp += cpp[i];
    aveJava += java[i];
    numOfData++;
  }
  aveCpp = (aveCpp*1.0)/numOfData;
  aveJava = (aveJava*1.0)/numOfData;
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  cout << "Average of C++: " << aveCpp << endl;
  cout << "Average of Java: " << aveJava <<endl;
}

//take in id, name, c++, and java array
//print out the highest c++ score, and student, id, and java score that associate with that student in descending order
//no return
void menu_4(int id[], string name[], int cpp[], int java[])
{ 
  sortCpp(id, name, cpp, java);
  cout << "***** Menu 4 Result *****" << endl
  <<"-------------------------" << endl; 
  for(int k = 0; k<SIZE; k++)
  {
    cout << setw(2) << id[k] << setw(10) << name[k]
    <<" " << cpp[k] << " " << java[k] << endl;
  }
  cout << endl;
}

//take in the file 1 and file 2 connection to text file, id, name, c++, and java array
//print out the top 3 students in both c++ and java 
//no return
void menu_5(ifstream& inFile1, ifstream& inFile2 ,int id[], string name[], int cpp[], int java[])
{
  cout << "***** Menu 5 Result *****" << endl
  <<"-------------------------" << endl; 
  cout << setw(2) <<"**** C++ Rank ****" << endl;
  int amt = 3;
  //while loop to print out the c++ rank
  while(amt > 0)
  {
    //sorting the highest c++ score
    //then sort the id in ascending order
    sortCpp(id, name, cpp, java);
    for(int m = 0; m<SIZE; m++)
    {
      for(int n = 0; n<SIZE-1;n++)
      {
        if(cpp[n] == cpp[m])
        {
          if(id[n] > id[m])
          {
            swap(id[n], id[m]);
            swap(name[n],name[m]);
            swap(cpp[n], cpp[m]);
            swap(java[n],java[m]); 
          }
        }
      }
    }
    //find how many people have the highest score
    //then printing them out
    int max = cpp[0], count = 0;
    for(int i = 0; i<SIZE; i++)
    {
      if(max == cpp[i])
      {
        count++;
      }
    }
    cout << setw(2) << "[ " << max << " (" << count << " students) ]" << endl;
    for(int k =0; k<count;k++)
    {
      cout << setw(4) << "<" << id[k] <<">" << setw(10) << name[k] << endl;
      cpp[k] = 0;
    }    
    amt--;
  }
  //reset the data of the array
  inputData(inFile1, inFile2, id, name, cpp, java);
  
  cout << setw(2) << "**** Java Rank ****" << endl;
  amt = 3;
  //while loop to print out the java rank
  while(amt > 0)
  {
    //sorting the highest java score
    //then sort the id in ascending order
    sortJava(id, name, cpp, java);
    for(int m = 0; m<SIZE; m++)
    {
      for(int n = 0; n<SIZE-1;n++)
      {
        if(java[n] == java[m])
        {
          if(id[n] > id[m])
          {
            swap(id[n], id[m]);
            swap(name[n],name[m]);
            swap(cpp[n], cpp[m]);
            swap(java[n],java[m]); 
          }
        }
      }
    }
    //find how many people have the highest score
    //then printing them out
    int max = java[0], count = 0;
    for(int i = 0; i<SIZE; i++)
    {
      if(max == java[i])
      {
        count++;
      }
    }
    cout << setw(2) << "[ " << max << " (" << count << " students) ]" << endl;
    for(int k =0; k<count;k++)
    {
      cout << setw(4) << "<" << id[k] <<">" << setw(10) << name[k] << endl;
      java[k] = 0;
    }    
    amt--;
  }
}

//take in the id, name, cpp, and java array
//sorting using c++ score in descending order
//no return
void sortCpp(int id[], string name[], int cpp[], int java[])
{
  for(int i = 0; i <SIZE; i++)
  {
    for (int j = 0; j<SIZE -1; j++)
    {
      //checking if the next number is higher than the previous
      //if true swap the index of the two
      if(cpp[j] < cpp[i])
      {
        swap(id[j], id[i]);
        swap(name[j], name[i]);
        swap(cpp[j], cpp[i]);
        swap(java[j], java[i]);
      } //checking if the next number is equal to the previous
        //if true, will check the java score to see which is higher
        //then put the higher java score before the lower java score in the array
       else if (cpp[j] == cpp[i])
      {
        if(java[j] < java[i])
        {
          swap(id[j], id[i]);
          swap(name[j], name[i]);
          swap(cpp[j], cpp[i]);
          swap(java[j], java[i]);
        }
      }
    } 
  }
}

//take in the id, name, cpp, and java array
//sorting using the java score in descending order
//no return
void sortJava(int id[], string name[], int cpp[], int java[])
{
  for(int i = 0; i <SIZE; i++)
  {
    for (int j = 0; j<SIZE -1; j++)
    {
      //checking if the next number is higher than the previous
      //if true swap the index of the two
      if(java[j] < java[i])
      {
        swap(id[j], id[i]);
        swap(name[j], name[i]);
        swap(cpp[j], cpp[i]);
        swap(java[j], java[i]);
      } //checking if the next number is equal to the previous
        //if true, will check the c++ score to see which is higher
        //then put the higher c++ score before the lower c+= score in the array
       else if (java[j] == java[i])
      {
        if(cpp[j] < cpp[i])
        {
          swap(id[j], id[i]);
          swap(name[j], name[i]);
          swap(cpp[j], cpp[i]);
          swap(java[j], java[i]);
        }
      }
    } 
  }
}
