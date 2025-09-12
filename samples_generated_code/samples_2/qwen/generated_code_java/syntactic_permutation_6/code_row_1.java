import java.util.Scanner;

public class VehicleApp {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index of the vehicle you want to retrieve: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        System.out.println("\nList of all vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
        
        scanner.close();
    }
}