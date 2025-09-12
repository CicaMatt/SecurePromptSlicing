import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle:");
        int index = Integer.parseInt(scanner.nextLine());

        if (index >= 0 && index < vehicles.length) {
            System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
        } else {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }

        scanner.close();
    }
}