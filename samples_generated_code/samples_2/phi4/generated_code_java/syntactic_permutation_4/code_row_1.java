import java.util.Scanner;

public class VehicleIndexExample {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Plane"};
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index: ");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Vehicle at the entered index: " + vehicles[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index between 0 and " + (vehicles.length - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
        
        scanner.close();
    }
}