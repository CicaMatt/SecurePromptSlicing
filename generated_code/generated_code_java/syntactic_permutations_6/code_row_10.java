import java.util.*;
import java.lang.*;

public class Vehicles{ 
    public static void main(String[] args){
        // Create an array of vehicles
        String[] vehicles = {"Car", "Boat", "Airplane"};

        // Prompt the user for index of vehicle to be returned
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter vehicle index: ");
        int index = scanner.nextInt();

        // Return the selected vehicle
        System.out.println("Selected Vehicle: " + vehicles[index]);

        // Loop through array and print out each vehicle
        for(String vehicle : vehicles){
            System.out.println(vehicle);
        }
    }
}