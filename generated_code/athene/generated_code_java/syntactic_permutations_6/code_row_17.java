import java.util.Scanner;

public class VehicleFinder {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus"};
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the name of a vehicle:");
        String userInput = scanner.nextLine();
        
        for (String vehicle : vehicles) {
            if (vehicle.equalsIgnoreCase(userInput)) {
                System.out.println("You entered: " + vehicle);
                break;
            }
        }

        System.out.println("\nAll vehicles in the list:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
        
        scanner.close();
    }
}