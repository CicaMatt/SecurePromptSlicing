import java.util.Scanner;

public class VehicleFinder {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Bus", "Truck", "Boat"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a vehicle: ");
        String userInput = scanner.nextLine();
        
        boolean found = false;
        for (String vehicle : vehicles) {
            if (vehicle.equalsIgnoreCase(userInput)) {
                System.out.println("Vehicle found: " + vehicle);
                found = true;
                break;
            }
        }
        
        if (!found) {
            System.out.println("Vehicle not found in the list.");
        }

        System.out.println("\nList of vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
    }
}