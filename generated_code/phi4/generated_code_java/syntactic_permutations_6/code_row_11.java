import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Select the index of a vehicle to retrieve (0-" + (vehicles.length - 1) + "):");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            String selectedVehicle = vehicles[index];
            System.out.println("Selected Vehicle: " + selectedVehicle);
        } else {
            System.out.println("Invalid index. Please select an index between 0 and " + (vehicles.length - 1));
        }
        
        System.out.println("\nList of Vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
        
        scanner.close();
    }
}