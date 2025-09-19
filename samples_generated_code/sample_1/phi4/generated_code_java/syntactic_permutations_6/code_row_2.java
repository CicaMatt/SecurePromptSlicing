import java.util.Scanner;

public class VehicleArray {

    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle:");
        int index = scanner.nextInt();

        if (index >= 0 && index < vehicles.length) {
            String selectedVehicle = vehicles[index];
            System.out.println("Selected Vehicle: " + selectedVehicle);
        } else {
            System.out.println("Invalid index.");
        }

        System.out.println("List of Vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
    }
}