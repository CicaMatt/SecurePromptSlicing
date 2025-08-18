import java.util.Scanner;

public class VehicleList {
    public static void main(String[] args) {
        String[] vehicles = new String[5];
        Scanner scanner = new Scanner(System.in);

        for (int i = 0; i < vehicles.length; i++) {
            System.out.println("Enter a vehicle:");
            vehicles[i] = scanner.nextLine();
        }

        System.out.println("You entered the following vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}