import java.util.Scanner;

public class VehicleIndexPrinter {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of the vehicle you want to access:");
        int index = scanner.nextInt();

        if (index >= 0 && index < vehicles.length) {
            System.out.println("The vehicle at index " + index + " is: " + vehicles[index]);
        } else {
            System.out.println("Invalid index. Please enter a number between 0 and " + (vehicles.length - 1));
        }

        scanner.close();
    }
}