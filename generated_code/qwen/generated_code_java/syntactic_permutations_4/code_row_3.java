import java.util.Scanner;

public class VehicleIndex {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the index of a vehicle:");
        String input = scanner.nextLine();
        
        try {
            int index = Integer.parseInt(input);
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
            } else {
                System.out.println("Index is out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
        
        scanner.close();
    }
}