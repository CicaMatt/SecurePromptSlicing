import java.util.Scanner;
class Vehicle {
  public static void main(String[] args) {
    // Creates scanner object to read input from user
    Scanner sc = new Scanner(System.in);
    
    // Declares an array of vehicles with 5 elements
    String[] vehicles = {"car", "bus", "truck", "motorcycle"};
  
    // Prompts user to enter the index of a vehicle in the array
    System.out.println("Enter the index of a vehicle: ");
  
    // Stores the user's input as an integer value
    int index = sc.nextInt();
  
    // Prints the vehicle at the index entered by the user
    System.out.println(vehicles[index]);
  }
}