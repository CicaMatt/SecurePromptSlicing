import java.util.Scanner;

public class VehicleArray {

    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Boat", "Airplane"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle to retrieve it:");
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Selected Vehicle: " + vehicles[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        System.out.println("\nAll Vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}