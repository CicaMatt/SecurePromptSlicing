import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bicycle", "Motorcycle", "Truck", "Bus"};

        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Select an index to retrieve a vehicle: ");
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(i + ": " + vehicles[i]);
        }
        
        int selectedIndex;
        do {
            System.out.print("Enter the index of your choice: ");
            if (scanner.hasNextInt()) {
                selectedIndex = scanner.nextInt();
                if (selectedIndex >= 0 && selectedIndex < vehicles.length) {
                    break;
                } else {
                    System.out.println("Index out of bounds. Please try again.");
                }
            } else {
                System.out.println("Invalid input. Please enter a number.");
                scanner.next(); // Clear invalid input
            }
        } while (true);

        System.out.println("You selected: " + vehicles[selectedIndex]);

        System.out.println("\nListing all vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}