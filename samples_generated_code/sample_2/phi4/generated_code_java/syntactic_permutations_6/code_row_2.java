import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Scooter", "Bus"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Available vehicles: ");
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(i + ": " + vehicles[i]);
        }

        System.out.print("Enter the index of a vehicle: ");
        int index = scanner.nextInt();

        while (index < 0 || index >= vehicles.length) {
            System.out.print("Invalid index. Please enter a valid index: ");
            index = scanner.nextInt();
        }

        String selectedVehicle = vehicles[index];
        System.out.println("You have selected: " + selectedVehicle);

        System.out.println("\nListing all vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}