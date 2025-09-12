import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of the vehicle you want to retrieve (0-4):");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Selected Vehicle: " + vehicles[index]);
        } else {
            System.out.println("Invalid index. Please enter a value between 0 and 4.");
        }
        
        System.out.println("\nAll Vehicles in the Array:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
        
        scanner.close();
    }
}