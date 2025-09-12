import java.util.Scanner;

public class VehicleArrayExample {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bicycle", "Truck", "Motorcycle", "Bus"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle you want to retrieve:");
        int index = scanner.nextInt();

        if (index >= 0 && index < vehicles.length) {
            System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
        } else {
            System.out.println("Invalid index.");
        }

        System.out.println("\nListing all vehicles:");

        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
    }
}