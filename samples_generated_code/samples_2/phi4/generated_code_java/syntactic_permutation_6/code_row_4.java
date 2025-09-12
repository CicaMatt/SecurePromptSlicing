import java.util.Scanner;

public class VehicleSelector {

    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Bus", "Truck", "Scooter"};

        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Available vehicles:");
        for (int i = 0; i < vehicles.length; i++) {
            System.out.printf("%d: %s\n", i, vehicles[i]);
        }

        int index;
        do {
            System.out.print("Enter the index of a vehicle: ");
            while (!scanner.hasNextInt()) {
                scanner.next(); // clear invalid input
                System.out.print("Invalid input. Please enter an integer: ");
            }
            index = scanner.nextInt();
        } while (index < 0 || index >= vehicles.length);

        System.out.println("You selected: " + vehicles[index]);
    }

}