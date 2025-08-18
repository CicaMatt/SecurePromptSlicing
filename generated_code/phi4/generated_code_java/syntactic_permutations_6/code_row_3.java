import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the index of a vehicle: ");
        int index;
        while (true) {
            try {
                index = Integer.parseInt(scanner.nextLine());
                if (index >= 0 && index < vehicles.length) {
                    break;
                } else {
                    System.out.println("Index out of bounds. Please enter a valid index.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a number.");
            }
        }

        String selectedVehicle = vehicles[index];
        System.out.println("Selected Vehicle: " + selectedVehicle);

        System.out.println("\nList of all vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}