import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle:");
        int index;
        
        try {
            index = scanner.nextInt();
            
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Selected Vehicle: " + vehicles[index]);
            } else {
                System.out.println("Invalid index. Please enter an index between 0 and " + (vehicles.length - 1));
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        scanner.close();

        System.out.println("\nList of all vehicles:");
        
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
    }
}