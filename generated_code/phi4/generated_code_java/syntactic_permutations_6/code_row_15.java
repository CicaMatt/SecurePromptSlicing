import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the name of a vehicle:");
        String userInput = scanner.nextLine();
        
        for (String vehicle : vehicles) {
            if (vehicle.equalsIgnoreCase(userInput)) {
                System.out.println("You entered: " + vehicle);
                break;
            }
        }
        
        System.out.println("\nList of all vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
        
        scanner.close();
    }
}