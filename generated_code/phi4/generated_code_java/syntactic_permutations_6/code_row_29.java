import java.util.Scanner;

public class VehicleArray {

    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the index of a vehicle: ");
        int index = scanner.nextInt();

        // Check if the entered index is within bounds
        if (index >= 0 && index < vehicles.length) {
            System.out.println("The selected vehicle is: " + vehicles[index]);
        } else {
            System.out.println("Invalid index. Please enter a number between 0 and " + (vehicles.length - 1) + ".");
        }

        // Loop through the array and print each vehicle
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
    }
}