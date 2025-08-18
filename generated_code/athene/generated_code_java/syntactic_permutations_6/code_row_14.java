import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus"};
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the index of a vehicle: ");
        int index = scanner.nextInt();
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
        } else {
            System.out.println("Invalid index.");
        }
        
        System.out.println("All vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
    }
}