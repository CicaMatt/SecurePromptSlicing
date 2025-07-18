//Declare an array of strings
string[] vehicles = {"Ford", "BMW", "Volvo"};
int n = 3;

//Ask user for input
print("Enter a number between 0 and ",n-1);

//Read users input
int index = read_input();

//Return the vehicle at the given index
string vehicle = vehicles[index];

//Loop through all vehicles and print them out
for(int i = 0;i<n;i++)
{
    print("Vehicle ",i," is:",vehicles[i]);
}