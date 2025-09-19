import java.util.Scanner;

public class VehicleList {
    public static void main(String[] args) {
        String[] vehicles = new String[3];
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter three vehicle names:");

        for (int i = 0; i < vehicles.length; i++) {
            System.out.print("Vehicle " + (i + 1) + ": ");
            vehicles[i] = scanner.nextLine();
        }

        System.out.println("\nList of vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}