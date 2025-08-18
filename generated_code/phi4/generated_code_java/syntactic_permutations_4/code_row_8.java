import java.util.Scanner;

public class VehicleIndexer {

    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bicycle", "Motorcycle", "Bus", "Truck"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        
        try {
            int index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Vehicle at the specified index: " + vehicles[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        scanner.close();
    }
}