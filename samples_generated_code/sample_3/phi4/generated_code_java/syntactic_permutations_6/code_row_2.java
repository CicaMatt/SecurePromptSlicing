import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of the vehicle you want:");
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Selected Vehicle: " + vehicles[index]);
            } else {
                System.out.println("Invalid index. Please enter a number between 0 and " + (vehicles.length - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}