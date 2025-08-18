import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the index of a vehicle:");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Selected Vehicle: " + vehicles[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a number.");
        }

        scanner.close();
    }
}