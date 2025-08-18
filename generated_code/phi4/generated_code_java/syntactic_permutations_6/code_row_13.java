import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);

        // Loop through the array and print out each vehicle
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        // Prompt the user for the index of a vehicle
        System.out.print("Enter the index of the vehicle you want: ");
        int index = scanner.nextInt();

        // Validate the input index
        if (index >= 0 && index < vehicles.length) {
            System.out.println("The selected vehicle is: " + vehicles[index]);
        } else {
            System.out.println("Invalid index. Please enter a number between 0 and " + (vehicles.length - 1));
        }

        scanner.close();
    }
}