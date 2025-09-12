import java.util.Scanner;

public class VehicleArray {

    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Scooter", "Bus"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle:");
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());

            if (index >= 0 && index < vehicles.length) {
                System.out.println("Selected Vehicle: " + vehicles[index]);
            } else {
                System.out.println("Index out of bounds. Please enter an index between 0 and " + (vehicles.length - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        System.out.println("\nList of Vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}