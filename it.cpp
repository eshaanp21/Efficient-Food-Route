#include <iostream>
#include <fstream>
#include <iomanip>
struct Values
{
  double fuel;
  double pserved;
};

struct position
{
  int row;
  int col;
};


std::string names();
bool greet(std::string);
int sizeread();
void transfer(Values**, int, std::ifstream&);
void printthemap1(int, Values**, std::string**);
void printthemap2(int, Values**, std::string**);
bool choices();



//group effort
int main() 
{
	std::string name = names();
	bool run = greet(name);

	std::ifstream in_file;
	in_file.open("text.txt");
	if (in_file.fail())
	{
		std::cout << "Cannot read from file" << std::endl;
		std::cout << "END PROGRAM";
		run = false;
	}
	int size;
	in_file >> size;
	std::cout << size << std::endl;

	//creates dynamically allocated 2d array
	Values **datamap = new Values*[size]; //* is blank space this fills second index
	for(int i = 0; i < size; i++) {
		datamap[i] = new Values[size]; //sets first index to same as second index, making it the same size
	}

	std::string** printmap = new std::string*[size];
	for(int i = 0; i < size; i++) {
		printmap[i] = new std::string[size]; //sets first index to same as second index, making it the same size
	}


	transfer(datamap, size, in_file);
	//tester code prints array
	for(int i = 0; i < size; i++) 
	{
		for(int j = 0; j < size; j++) {
			std::cout << std::fixed << std::setprecision(2) << datamap[i][j].fuel << " ";
			std::cout << datamap[i][j].pserved << "   ";
		}
		std::cout << std::endl;
	}
  // for(int i = 0; i < size; i++) 
  // {
  //   for(int j = 0; j < size; j++) {
  //     std::cout << datamap[i][j].pserved << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // printthemap2(size, datamap, printmap);
	// printthemap1(size, datamap, printmap);
	
	bool option = choices();
	if(option)
	{
		printthemap2(size, datamap, printmap);
	}
	else
	{
    printthemap1(size, datamap, printmap);
  }

  // while(run)
  // {
    
  // }

    for(int i = 0; i < size; i++)
    {
	   delete[] datamap[i];
	}
	delete[] datamap;
} 


//copied from previous program Moneeb
std::string names()
{
  std::string name;
  std::cout << "Hello and welcome! What is your name? ";
  std::cin >> name;
  return name;
}


//copied from previous program Eshaan
bool greet(std::string name)
{
  std::string input;
  std::cout << "Hi " << name << ". With this program, we are looking to make steps toward creating a solution for poverty." << std::endl;

  std::cout << "You can give us a file with a map of an area, including the amount of gas it will take to reach an area and the amount of people we can serve." << std::endl;

  std::cout << "With this map, we can calculate a route depending on which statistic you care about the most." << std::endl;

  std::cout << "Would you like to continue or exit the program? ";
  while(true)
  {
    std::cin >> input;
    if(input == "continue")
    {
      return true;
    }
    else if(input == "quit")
    {
      std::cout << "Thanks for considering our program! Have a nice day." << std::endl;
      return false;
    }
    std::cout << "Please enter a valid input (continue or quit): ";
  } 
}


//Eshaan
void transfer(Values** datamap, int size, std::ifstream& in_file)
{
  for(int i = 0; i < size; i++) 
  {
    for(int j = 0; j < size; j++) {
      in_file >> datamap[i][j].fuel;
      in_file >> datamap[i][j].pserved;
    }
  }
  std::cout << std::endl;
}


//Moneeb
bool choices()
{
  int userchoice;
  std::cout << "Which option would you like to choose?\n";
  std::cout << "Option 1: Maximizes the number of people served\n";
  std::cout << "Option 2: Minimizes the amount of fuel used\n";
  std::cout << "Option 3: Maximizes the areas of region covered\n";
  std::cin >> userchoice;
  if (userchoice == 2 || userchoice == 3)
  {
    return true;
  }
  else 
  {
    return false;
  }
}

void printthemap2(int size, Values** datamap, std::string** printmap)
{
  position temp;
  double fuelcount = datamap[0][0].fuel;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      printmap[i][j] = "-";
    }
  }
  

  printmap[0][0] = "X";
  temp.row = 0;
  temp.col = 0;
  int row = 0;
  int col = 0;
  

  while (fuelcount <= 12.0)
  {
      
      bool top2 = false;
      bool bot2 = false;
      bool left2 = false;
      bool right2 = false;

      bool first = true;

      int top = row-1;
      if(top >= 0)
      {
        if ((datamap[temp.row][temp.col].fuel > datamap[row-1][col].fuel) || first)
        {
          temp.row = row-1;
          temp.col = col;
          first = false;
        }
        top2 = true;
      }

      int left = col-1;
      if(left >= 0)
      {
        if((datamap[temp.row][temp.col].fuel > datamap[row][col-1].fuel) || first)
        {
          temp.row = row;
          temp.col = col-1;
          first = false;
        }
        left2 = true;
      }

      int right = col+1;
      if(right < 5)
      {
        if((datamap[temp.row][temp.col].fuel > datamap[row][col+1].fuel) || first)
        {
          temp.row = row;
          temp.col = col+1;
          first = false;
        }
        right2 = true;
      }

      int bot = row+1;
      if(bot <  5)
      {
        if((datamap[temp.row][temp.col].fuel > datamap[row+1][col].fuel) || first)
        {
          temp.row = row+1;
          temp.col = col;
          first = false;
        }
        bot2 = true;
      }

      if (top2)
      {
        if(left2)
        {
          if((datamap[temp.row][temp.col].fuel > datamap[row-1][col-1].fuel) || first)
          {
            temp.row = row-1;
            temp.col = col-1;
            first = false;
          }
        }

        if(right2)
        {
          if(datamap[temp.row][temp.col].fuel > datamap[row-1][col+1].fuel)
          {
            temp.row = row-1;
            temp.col = col+1;
            first = false;
          }
        }
      }

      if(bot2)
      {
        if(left2)
        {
          if(datamap[temp.row][temp.col].fuel > datamap[row+1][col-1].fuel || first)
          {
            temp.row = row+1;
            temp.col = col-1;
            first = false;
          }
        }
      
        if(right2)
        {
          if(datamap[temp.row][temp.col].fuel > datamap[row+1][col+1].fuel || first)
          {
            temp.row = row+1;
            temp.col = col+1;
            first = false;
          }
        }
      }

      printmap[temp.row][temp.col] = "X";
      fuelcount = fuelcount + datamap[temp.row][temp.col].fuel;
      datamap[temp.row][temp.col].pserved = -1;
      row = temp.row;
      col = temp.col;
  }

  std::cout << fuelcount << " ";

  if (fuelcount>12.0)
  {
    printmap[temp.row][temp.col] = "-";
    fuelcount = fuelcount - datamap[temp.row][temp.col].fuel;
  }

  std::cout << fuelcount << std::endl;
  for (int i=0; i<size; i++)
  {
    for (int j=0; j<size; j++)
    {
      std::cout<<printmap[i][j];
    }
    std::cout<<"\n";
  }
}


void printthemap1(int size, Values** datamap, std::string** printmap)
{
  position temp;
  double fuelcount = datamap[0][0].fuel;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      printmap[i][j] = "-";
    }
  }
  

  printmap[0][0] = "X";
  temp.row = 0;
  temp.col = 0;
  int row = 0;
  int col = 0;
  

  while (fuelcount <= 12.0)
  {
    bool top2 = false;
    bool bot2 = false;
    bool left2 = false;
    bool right2 = false;

    bool first = true;

    int top = row-1;
    if(top >= 0)
    {
      if ((datamap[temp.row][temp.col].pserved < datamap[row-1][col].pserved) || first)
      {
        temp.row = row-1;
        temp.col = col;
        first = false;
      }
      top2 = true;
    }

    int left = col-1;
    if(left >= 0)
    {
      if((datamap[temp.row][temp.col].pserved < datamap[row][col-1].pserved) || first)
      {
        temp.row = row;
        temp.col = col-1;
        first = false;
      }
      left2 = true;
    }

    int right = col+1;
    if(right < 5)
    {
      if((datamap[temp.row][temp.col].pserved < datamap[row][col+1].pserved) || first)
      {
        temp.row = row;
        temp.col = col+1;
        first = false;
      }
      right2 = true;
    }

    int bot = row+1;
    if(bot <  5)
    {
      if((datamap[temp.row][temp.col].pserved < datamap[row+1][col].pserved) || first)
      {
        temp.row = row+1;
        temp.col = col;
        first = false;
      }
      bot2 = true;
    }

    if (top2)
    {
      if(left2)
      {
        if((datamap[temp.row][temp.col].pserved < datamap[row-1][col-1].pserved) || first)
        {
          temp.row = row-1;
          temp.col = col-1;
          first = false;
        }
      }

      if(right2)
      {
        if((datamap[temp.row][temp.col].pserved < datamap[row-1][col+1].pserved) || first)
        {
          temp.row = row-1;
          temp.col = col+1;
          first = false;
        }
      }
    }

    if(bot2)
    {
      if(left2)
      {
        if((datamap[temp.row][temp.col].pserved < datamap[row+1][col-1].pserved) || first)
        {
          temp.row = row+1;
          temp.col = col-1;
          first = false;
        }
      }
      
      if(right2)
      {
        if((datamap[temp.row][temp.col].pserved < datamap[row+1][col+1].pserved) || first)
        {
          temp.row = row+1;
          temp.col = col+1;
          first = false;
        }
      }
    }

      printmap[temp.row][temp.col] = "X";
      fuelcount = fuelcount + datamap[temp.row][temp.col].fuel;
      datamap[temp.row][temp.col].pserved = -1;
      row = temp.row;
      col = temp.col;
  }

  std::cout << fuelcount << " ";
  
  if (fuelcount>12.0)
  {
    printmap[temp.row][temp.col] = "-";
    fuelcount = fuelcount - datamap[temp.row][temp.col].fuel;
  }

  std::cout << fuelcount << std::endl;
  for (int i=0; i<size; i++)
  {
    for (int j=0; j<size; j++)
    {
      std::cout<<printmap[i][j];
    }
    std::cout<<"\n";
  }
}







