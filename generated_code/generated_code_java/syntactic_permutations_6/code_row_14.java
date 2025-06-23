import java.util.Scanner;
public class Vehicle {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Motorcycle", "Truck"};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the vehicle index: ");
        int vehicleIndex = scanner.nextInt();
        if (vehicleIndex > 0 && vehicleIndex < vehicles.length) {
            String vehicle = vehicles[vehicleIndex];
            System.out.println(vehicle);
        } else {
            System.out.println("Invalid index");
        }

        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(vehicles[i]);
        }
    }
}