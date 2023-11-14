#include <iostream> //library for input and output
#include <fstream> //library to use file stream for the text file
#include <iomanip> //library for formatting

struct Values //struct to hold given data
{
  double fuel; //holds amount of fuel that will be used
  double pserved; //holds amount of people that will be served
};

struct position //struct to hold and print the positions of the route
{
  int row; //holds the number of row
  int col; //holds the number of col
};

//i is increasing for each recursion
std::string names(); //lets computer know function names() exists
bool greet(std::string); //lets computer know function greet() exists
int sizeread();//lets computer know function sizeread() exists
void transfer(Values**, int, std::ifstream&); //lets computer know function transfer() exists
void printthemap1(int, Values**, std::string**); //lets computer know function printthemap1() exists
void printthemap2(int, Values**, std::string**); //lets computer know function printthemap2() exists
bool choices(); //lets computer know function choices() exists
bool torep(); //lets computer know function torep() exists


//group effort
int main() 
{
	std::string name = names(); //sets string variable "name" equal to whatever function names() returns
	bool run = greet(name); //sets boolean variable "run" equal to whatever function greet() returns
	std::ifstream in_file; //created file stream named "in_file"
  while (run) //while loop created for if user wants to repeat or not, at the start set to true
  {
    in_file.open("test.txt"); //opens text file 
    if (in_file.fail()) //checks if text file exists 
    {
      std::cout << "Cannot read from file" << std::endl;
      std::cout << "END PROGRAM";
      run = false; //ends program
    }
    int size; //intializes integer variable "size"
    in_file >> size; //takes first value from text file and inputs it into variable "size"
    std::cout<<"\nThis is the data you entered: "; 
    
    //creates dynamically allocated 2d array
    Values **datamap = new Values*[size]; //* is blank space this fills second index
    for(int i = 0; i < size; i++) {
      datamap[i] = new Values[size]; //sets first index to same as second index, making it the same size
    }
    std::string** printmap = new std::string*[size];//* is blank space this fills second index
    for(int i = 0; i < size; i++) {
      printmap[i] = new std::string[size]; //sets first index to same as second index, making it the same size
    }
    
    //moves data from file to array
    transfer(datamap, size, in_file); //calls function transfer()
    //tester code prints array
    for(int i = 0; i < size; i++) 
    {
      for(int j = 0; j < size; j++) {
        std::cout << std::fixed << std::setprecision(2) << datamap[i][j].fuel << " "; //puts all values in data to print with two decimal places, and puts space after each one
        std::cout << datamap[i][j].pserved << "   "; //formatting, puts a tab after each value
      }
      std::cout << std::endl;
    }
    bool option = choices(); //boolean initialized called "option" and set equal to function choices()
    if(option) //if option == true
    {
      printthemap2(size, datamap, printmap); //calls function to print second map, this is map for choice 2 and 3
    }
    else //if option != true
    {
      printthemap1(size, datamap, printmap); //calls function to print first map, for choice 1
    }
    in_file.close(); //closes file stream
    for(int i = 0; i < size; i++) 
    {
      delete[] datamap[i]; //deletes every value in dynamically allocated array to hold given data
    }
    delete[] datamap; //deletes array
    for(int i = 0; i < size; i++)
    {
      delete[] printmap[i]; //deletes every value in dynamically allocated array that holds route locations
    }
    delete[] printmap; //deletes array
    run = torep(); //calls function torep()
  }
  std::cout<<"Thank you for using our program. Have a great day!\n"; //ending statement
} 


//Moneeb
//asks user for their name
//string function
//returns user name
std::string names() 
{
  std::string name; //string variable initialized
  std::cout << "Hello and welcome! What is your name? ";
  std::cin >> name; //user input taken in variable name
  return name; //returns user input
}


//copied from previous program Eshaan
//boolean function
//passes function users name
//gives user description of the program
//lets user choose if they would like to continue of exit the program
//returns true or false
bool greet(std::string name)
{
  std::string input; //initializes string variable called input
  std::cout << "\nHi " << name << ". This program helps to make a step towards aiding poverty in certain areas." << std::endl;
  std::cout << "You can enter a file with the map of an area which includes the amount of gas it will take to reach \ncertain regions and the amount of people that can be served in that region." << std::endl;
  std::cout << "With this information, the program can calculate a route depending on which statistic you want to base your route around." << std::endl;
  std::cout << "\nWould you like to continue or exit the program? "; //asks user if they would like to continue
  while(true) //while loop set to true, will always run
  {
    std::cin >> input; //takes in user input
    if(input == "continue") //checks to see if user input "continue"
    {
      return true; //function returns true
    }
    else if(input == "exit") //checks to see if user input "exit"
    {
      std::cout << "Thanks for considering our program! Have a nice day." << std::endl; //ending statement
      return false; //function returns false
    }
    std::cout << "Please enter a valid input (continue or exit): "; //input validion if user did not into any of the if-statements
  } 
}


//Eshaan
//void function
//transfer data from the .txt file to the dynamically allocated 2d array
void transfer(Values** datamap, int size, std::ifstream& in_file)
{
  for(int i = 0; i < size; i++) //for loop for each row 
  {
    for(int j = 0; j < size; j++) { //for loop for each colomn
      in_file >> datamap[i][j].fuel; //take next double type from file and assign it to the fuel value of struct in the index [i][j]
      in_file >> datamap[i][j].pserved; ////take next double type from file and assign it to the pserved value of struct in the index [i][j]
    }
  }
  std::cout << std::endl;
}


//Moneeb
//boolean function
//displays options to user 
//allows user to pick option
//returns true or false based on option user chose
bool choices()
{
  std::string userchoice; //intialized string variable 
  std::cout << "\nHere are your options: \n"; 
  std::cout << "Option 1: Maximizes the number of people served\n";
  std::cout << "Option 2: Minimizes the amount of fuel used\n";
  std::cout << "Option 3: Maximizes the areas of region covered\n";
  std::cout << "\nWhich option would you like to choose? ";
  std::cin >> userchoice; //takes in user option
  while(true) //while loop set to always run
  {
    if (userchoice == "2" || userchoice == "3") //checks if user chose option 2 or 3
    {
      return true; //function returns true
    }
    else if(userchoice == "1") //checks if user chose option 1
    {
      return false; //returns 1
    }
    else //if none of if-statements are entered
    {
      std::cout << "Please enter a valid input(1, 2, or 3): "; //input validation
      std::cin >> userchoice; //input validation, takes in user input again
    }
  }
}

//Collaboration 
//void function
//used to print map for options 2 and 3
//passes function data size, array holding given data, and empty array to print map
void printthemap2(int size, Values** datamap, std::string** printmap)
{
  position temp; //variable initialized as struct postion
  int pcount = datamap[0][0].pserved; //initializes and sets pcount to first value in the array, only the value that is in pserved part of the struct 
  double fuelcount = datamap[0][0].fuel; //initializes and sets fuelcount to first value in the array, only the value that is in fuel part of the struct
  datamap[0][0].fuel = 900; //changes first fuel value to 900
  for (int i = 0; i < size; i++) 
  {
    for (int j = 0; j < size; j++)
    {
      printmap[i][j] = "-"; //sets all values in printmap array to "-"
    }
  }
  printmap[0][0] = "X"; //sets first value in printmap array to "X"
  temp.row = 0; //temporarily holds the row position of the next possible best move
  temp.col = 0; //temporarily holds the column position of the next possible best move
  int row = 0; //holds the row position of the location we are moving out of
  int col = 0; //holds the column position of the location we are moving out of
  int ph; //placeholder variable for later calculations
  int regioncover = 1; //initializes variable to count number of regions covered
  std::cout << std::endl << "Read from left to right (start at (Row: 1, Col: 1): " << std::endl;
  while (fuelcount <= 12.0) //while fuel is still left
  {
      bool top2 = false; //true if the top row is open
      bool bot2 = false; //true if the bottome row is open
      bool left2 = false; //true if the left column is open
      bool right2 = false; //true if the right column is open
      bool first = true; //false if there has already been a first available move
      int top = row-1; //sets top to row value next to current position
      if(top >= 0) //if there is a row available
      {
        if ((datamap[temp.row][temp.col].fuel >= datamap[row-1][col].fuel) || first) //if we use less fuel for this new posision compared to the current temp or if it is the first available
        {
          temp.row = row-1; //temporarily save row
          temp.col = col; //temporarily save column
          first = false; //set to false because now the first option has appeared
        }
        top2 = true; //row is available
      }

      //this portion is more or less the same as the previous except we are checking the left column instead of the row above the current position
      int left = col-1; //sets left to next column
      if(left >= 0) //checks if it exists
      {
        if((datamap[temp.row][temp.col].fuel >= datamap[row][col-1].fuel) || first) //compares left position with current temp
        {
          temp.row = row; //sets temp positions to the new best option
          temp.col = col-1;
          first = false; //sets first to false because there will no longer be a first
        }
        left2 = true; //the left column is available
      }

      //this portion is more or less the same as the previous except we are checking the right column instead of the left
      int right = col+1; //sets right to next column to the right
      if(right < size) //if that column exists
      {
        if((datamap[temp.row][temp.col].fuel >= datamap[row][col+1].fuel) || first) //compare current best position with right position
        {
          temp.row = row; //sets temp positions to the new best option
          temp.col = col+1;
          first = false; //sts first to false because there will no longer be a first
        }
        right2 = true; //the right column is available
      }

      //same as previous
      int bot = row+1;
      if(bot <  size)
      {
        if((datamap[temp.row][temp.col].fuel >= datamap[row+1][col].fuel) || first)
        {
          temp.row = row+1;
          temp.col = col;
          first = false;
        }
        bot2 = true;
      }

      if (top2) //if there is a top row
      {
        if(left2) //if there is a left column (top + left is top left)
        {
          if((datamap[temp.row][temp.col].fuel >= datamap[row-1][col-1].fuel) || first) //compare the new position with the current best
          {
            temp.row = row-1; //sets temp positions to new best option
            temp.col = col-1;
            first = false; //sets first to false because there will no longer be a first
          }
        }
        if(right2) //if there is a right column (top right)
        {
          if(datamap[temp.row][temp.col].fuel >= datamap[row-1][col+1].fuel || first) //compare the new position with the current best
          {
            temp.row = row-1; //sets temp positions to new best option
            temp.col = col+1;
            first = false; //sets first to false because there will no longer be a first
          }
        }
      }
      if(bot2) //if there is a bottom row
      {
        if(left2) //if there is a left column (bottom left)
        {
          if(datamap[temp.row][temp.col].fuel >= datamap[row+1][col-1].fuel || first)  //compare the new position with the current best
          {
            temp.row = row+1; //sets temp positions to new best option
            temp.col = col-1;
            first = false; //sets first to false because there will no longer be a first
          }
        }
        if(right2) //if there is a right column (bottom right)
        {
          if(datamap[temp.row][temp.col].fuel >= datamap[row+1][col+1].fuel || first)  //compare the new position with the current best
          {
            temp.row = row+1; //sets temp positions to new best option
            temp.col = col+1;
            first = false; //sets first to false because there will no longer be a first
          }
        }
      }  
      printmap[temp.row][temp.col] = "X"; //sets the next best move saved to temp to character X in print array
      pcount = pcount + datamap[temp.row][temp.col].pserved; //calculates pcount for the move just made
      fuelcount = fuelcount + datamap[temp.row][temp.col].fuel; //calculate fuelcount for the move just made
      ph = datamap[temp.row][temp.col].fuel; //saves fuel before we change it to make it so we cant go back
      datamap[temp.row][temp.col].fuel = 900; //sets fuel to 900 making it unreachable
      row = temp.row; //sets new starting point to row
      col = temp.col; //sets new starting point to column
      regioncover++; //adds one to total regions covered
      if(fuelcount <= 12) //if the move is valid print it
      {
        std::cout << "Move to: (Row: " << row+1 << ", Col: " << col+1 << ")   " << std::endl;
      }
  }
  std::cout << std::endl;
  if (fuelcount>12.0) //if the final move went over 12 fuel
  {
    printmap[temp.row][temp.col] = "-"; //reset position in printmap
    fuelcount = fuelcount - ph; //remove last move fuel
    pcount = pcount - datamap[temp.row][temp.col].pserved; //remove last move people
    regioncover--; //remove last move region count
  }

  //print map
  std::cout<<std::endl<<"  * Map Route *\n";
  for (int i=0; i<size; i++) //row for loop
  {
    for (int j=0; j<size; j++) //col for loop
    {
      std::cout<<"  "<<printmap[i][j]; //print index
    }
    std::cout<<"\n";
  }
  std::cout << "\nFuel Used: " << fuelcount << std::endl; //print fuel
  std::cout << "People Served: " << pcount << std::endl; //print people served
  std::cout << "Regions Covered: " << regioncover << std::endl; //print regions covered

}

//Collaboration 
//void function
//used to print map for option 1
//passes function data size, array holding given data, and empty array to print map
void printthemap1(int size, Values** datamap, std::string** printmap)
{
  position temp; //variable initialized as struct postion
  double fuelcount = datamap[0][0].fuel;  //initializes and sets fuel to first value in the array, only the value that is in fuel part of the struct 
  int pcount = datamap[0][0].pserved; //initializes and sets pcount to first value in the array, only the value that is in pserved part of the struct 
  datamap[0][0].pserved = -1; //changes pserved fuel value to -1
  for (int i = 0; i < size; i++) //loop through rows
  {
    for (int j = 0; j < size; j++) //loop through columns
    {
      printmap[i][j] = "-"; //set print map to blank - never traveled
    }
  }
  printmap[0][0] = "X"; //sets first value in printmap array to "X"
  temp.row = 0; //temporarily holds the row position of the next possible best move
  temp.col = 0; //temporarily holds the column position of the next possible best move
  int row = 0; //holds the row position of the location we are moving out of
  int col = 0; //holds the column position of the location we are moving out of
  int ph; //placeholder variable for later calculations
  int regioncover = 1; //initializes variable to count number of regions covered
  std::cout << std::endl << "Read from left to right (start from (Row: 1, Col: 1)): " << std::endl;
  while (fuelcount <= 12.0) //while fuel is still left
  {
    bool top2 = false; //true if the top row is open
    bool bot2 = false; //true if the bottome row is open
    bool left2 = false; //true if the left column is open
    bool right2 = false; //true if the right column is open
    bool first = true; //false if there has already been a first available move
    int top = row-1; //sets top to row value next to current position
    if(top >= 0) //if there is a row available
    {
      if ((datamap[temp.row][temp.col].pserved <= datamap[row-1][col].pserved) || first) //if we see more people at the new position compared to temp or if it is the first available
      {
        temp.row = row-1; //temporarily save row
        temp.col = col; //temporarily save column
        first = false; //set to false because now the first option has appeared
      }
      top2 = true; //row is available
    }

    //this portion is more or less the same as the previous except we are checking the left column instead of the row above the current position
    int left = col-1; //sets left to next column
    if(left >= 0) //checks if it exists
    {
      if((datamap[temp.row][temp.col].pserved <= datamap[row][col-1].pserved) || first) //compares left position with current temp
      {
        temp.row = row; //sets temp positions to the new best option
        temp.col = col-1;
        first = false; //sets first to false because there will no longer be a first
      }
      left2 = true; //the left column is available
    }
    //this portion is more or less the same as the previous except we are checking the right column instead of the left
    int right = col+1; //sets right to next column to the right
    if(right < size) //if that column exists
    {
      if((datamap[temp.row][temp.col].pserved <= datamap[row][col+1].pserved) || first) //compare current best position with right position
      {
        temp.row = row; //sets temp positions to the new best option
        temp.col = col+1;
        first = false; //sts first to false because there will no longer be a first
      }
      right2 = true; //the right column is available
    }

    //same as previous
    int bot = row+1;
    if(bot <  size)
    {
      if((datamap[temp.row][temp.col].pserved <= datamap[row+1][col].pserved) || first)
      {
        temp.row = row+1;
        temp.col = col;
        first = false;
      }
      bot2 = true;
    }

    if (top2) //if there is a top row
    {
      if(left2) //if there is a left column (top + left is top left)
      {
        if((datamap[temp.row][temp.col].pserved <= datamap[row-1][col-1].pserved) || first) //compare the new position with the current best
        {
          temp.row = row-1; //sets temp positions to new best option
          temp.col = col-1;
          first = false; //sets first to false because there will no longer be a first
        }
      }

      if(right2) //if there is a right column (top right)
      {
        if((datamap[temp.row][temp.col].pserved <= datamap[row-1][col+1].pserved) || first) //compare the new position with the current best
        {
          temp.row = row-1; //sets temp positions to new best option
          temp.col = col+1;
          first = false; //sets first to false because there will no longer be a first
        }
      }
    }

    if(bot2) //if there is a bottom row
    {
      if(left2) //if there is a left column (bottom left)
      {
        if((datamap[temp.row][temp.col].pserved <= datamap[row+1][col-1].pserved) || first)  //compare the new position with the current best
        {
          temp.row = row+1; //sets temp positions to new best option
          temp.col = col-1;
          first = false; //sets first to false because there will no longer be a first
        }
      }
      
      if(right2) //if there is a right column (bottom right)
      {
        if((datamap[temp.row][temp.col].pserved <= datamap[row+1][col+1].pserved) || first)  //compare the new position with the current best
        {
          temp.row = row+1; //sets temp positions to new best option
          temp.col = col+1;
          first = false; //sets first to false because there will no longer be a first
        }
      }
    }
      printmap[temp.row][temp.col] = "X"; //sets the next best move saved to temp to character X in print array
      fuelcount = fuelcount + datamap[temp.row][temp.col].fuel; //calculates fuelcount for the move just made
      pcount = pcount + datamap[temp.row][temp.col].pserved; //calculate pserved for the move just made
      ph = datamap[temp.row][temp.col].pserved; //saves pserved before we change it to make it so we cant go back
      datamap[temp.row][temp.col].pserved = -1; //sets pserved to -1 making it unreachable
      row = temp.row; //sets new starting point to row
      col = temp.col; //sets new starting point to column
      regioncover++; //adds one to total regions covered
      if(fuelcount <= 12) //if the move is valid print it
      {
        std::cout << "Move to: (Row: " << row+1 << ", Col: " << col+1 << ")   " << std::endl;
      }
      
  }
  std::cout << std::endl;
  if (fuelcount>12.0) //if the final move went over 12 fuel
  {
    printmap[temp.row][temp.col] = "-"; //reset position in printmap
    fuelcount = fuelcount - datamap[temp.row][temp.col].fuel; //remove last move fuel
    pcount = pcount - ph; //remove last move pcount
    regioncover--; //remove last move region count
  }

  //print map
  std::cout<<"\n  * Map Route *\n";
  for (int i=0; i<size; i++)  //row for loop
  {
    for (int j=0; j<size; j++) //col for loop
    {
      std::cout<<"  "<<printmap[i][j]; //print index
    }
    std::cout<<"\n";
  }
  std::cout << "\nFuel Used: " << fuelcount << std::endl; //print fuel
  std::cout<<"People Served: " <<pcount << std::endl; //print people served
  std::cout << "Regions Covered: " << regioncover << std::endl; //print regions covered
}

//Moneeb
//boolean function
//asks user if they want to repeat or quit the program
//returns true or false depending or user input
bool torep()
{
  std::string repinput; //initializes string variable named repinput
  std::cout<<"\nWould you like to repeat or quit the program? "; //asks user if they want to repeat program or quit it
  std::cin>>repinput; //takes in user input with repinput variable
  while (true) //while loop set to always run
  {
    if (repinput == "repeat") //checks if user input "repeat"
    {
      return true; //function returns true
    }
    else if (repinput == "quit") //checks if user input "quit"
    {
      return false; //function returns false
    }//if user gets past if statements, they did not choose one of the given options
    std::cout<< "Please enter a valid input (repeat or quit): "; //input validation
    std::cin>>repinput; //asks user for their choice again
  }
}
