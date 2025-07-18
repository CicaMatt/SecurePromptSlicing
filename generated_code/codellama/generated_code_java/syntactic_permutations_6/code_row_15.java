import java.util.*;

public class Vehicles {
    public static void main(String[] args) {
        // create an array of strings called vehicles
        String[] vehicles = {"car", "boat", "airplane"};
        
        // prompt the user and return that vehicle
        System.out.println("Which vehicle would you like to take?");
        Scanner scanner = new Scanner(System.in);
        String vehicle = scanner.nextLine();
        System.out.println("You have chosen the " + vehicle);
        
        // loop through the array and print out each vehicle
        for (String v: vehicles) {
            System.out.println(v);
        }
    }
}