import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of a vehicle (0 to 4):");
        
        try {
            int index = Integer.parseInt(scanner.nextLine());
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Selected Vehicle: " + vehicles[index]);
            } else {
                System.out.println("Invalid index. Please enter a number between 0 and 4.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter an integer.");
        }
        
        scanner.close();
    }
}