import java.util.Scanner;

public class VehicleApp {
    public static void main(String[] args) {
        String[] vehicles = new String[5];
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter 5 vehicles:");
        for (int i = 0; i < vehicles.length; i++) {
            System.out.print("Vehicle " + (i + 1) + ": ");
            vehicles[i] = scanner.nextLine();
        }

        System.out.println("\nYou entered the following vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}