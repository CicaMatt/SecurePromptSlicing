import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Scooter", "Bus"};
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Available vehicles:");
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(i + ": " + vehicles[i]);
        }
        
        int index;
        do {
            System.out.print("Enter the index of a vehicle: ");
            while (!scanner.hasNextInt()) {
                String input = scanner.next();
                System.out.printf("\"%s\" is not valid input. Please enter an integer.\n", input);
            }
            index = scanner.nextInt();
        } while (index < 0 || index >= vehicles.length);

        System.out.println("Selected vehicle: " + vehicles[index]);

        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
}