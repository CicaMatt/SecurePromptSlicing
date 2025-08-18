import java.util.Scanner;

public class VehicleManager {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        String[] vehicles = {"Car", "Bike", "Truck", "Bus"};
        
        System.out.print("Enter the index of a vehicle: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Selected Vehicle: " + vehicles[index]);
        } else {
            System.out.println("Invalid index.");
        }
        
        System.out.println("\nAll Vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}