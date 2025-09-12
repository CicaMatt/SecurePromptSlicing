import java.util.Scanner;

public class VehicleIndex {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        scanner.close();
    }
}