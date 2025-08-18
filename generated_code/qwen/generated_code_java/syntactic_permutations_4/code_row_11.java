import java.util.Scanner;

public class VehicleIndexAccess {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};

        System.out.println("Enter an index to access a vehicle:");
        try {
            int index = Integer.parseInt(scanner.nextLine());
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid integer.");
        }

        scanner.close();
    }
}