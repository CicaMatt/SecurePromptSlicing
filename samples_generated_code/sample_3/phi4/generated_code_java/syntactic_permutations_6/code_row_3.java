import java.util.Scanner;

public class VehicleArray {

    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Boat"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle:");
        int index = scanner.nextInt();

        if (index >= 0 && index < vehicles.length) {
            System.out.println("Selected vehicle: " + vehicles[index]);
        } else {
            System.out.println("Invalid index.");
        }

        System.out.println("\nListing all vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}