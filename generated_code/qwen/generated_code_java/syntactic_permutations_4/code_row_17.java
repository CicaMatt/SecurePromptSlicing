import java.util.Scanner;

public class VehicleIndex {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle (0 to 4):");
        int index = scanner.nextInt();

        if (index >= 0 && index < vehicles.length) {
            System.out.println("The selected vehicle is: " + vehicles[index]);
        } else {
            System.out.println("Invalid index. Please enter a number between 0 and 4.");
        }

        scanner.close();
    }
}