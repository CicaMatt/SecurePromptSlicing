import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Please enter the index of the vehicle you want to retrieve:");
        
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
                System.out.println("Invalid input. Please enter a numeric value for the index.");
            }
        }

        String selectedVehicle = vehicles[index];
        System.out.println("Selected Vehicle: " + selectedVehicle);

        System.out.println("\nList of all Vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}