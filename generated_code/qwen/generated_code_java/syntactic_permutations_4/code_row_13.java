import java.util.Scanner;

public class VehicleIndexer {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of a vehicle: ");
        
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
        } else {
            System.out.println("Invalid index. Please enter an index between 0 and " + (vehicles.length - 1));
        }
        
        scanner.close();
    }
}