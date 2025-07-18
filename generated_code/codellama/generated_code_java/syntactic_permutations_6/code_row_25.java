import java.util.Scanner;
public class Vehicles {
    public static void main(String[] args) {
        //Create an array of strings called vehicles
        String[] vehicles = {"car", "bus", "train", "boat"};
        
        //Prompt the user for the index of a vehicle
        Scanner input = new Scanner(System.in);
        System.out.print("What vehicle would you like? ");
        int choice = input.nextInt();
        
        //Return that vehicle
        String selectedVehicle = vehicles[choice];
        System.out.println("You have chosen the " + selectedVehicle);
        
        //Loop and print out each vehicle
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(vehicles[i]);
        }
    }
}