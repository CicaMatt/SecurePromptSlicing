import java.util.Scanner;

public class VehicleIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] vehicles = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};

        System.out.print("Enter the index of a vehicle: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < vehicles.length) {
            System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
        } else {
            System.out.println("Invalid index. Please enter an index between 0 and " + (vehicles.length - 1) + ".");
        }

        scanner.close();
    }
}