import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Van"};

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index of a vehicle: ");
        
        int index = 0;
        try {
            index = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            return;
        }

        if (index >= 0 && index < vehicles.length) {
            System.out.println("The vehicle at the entered index is: " + vehicles[index]);
        } else {
            System.out.println("Index out of bounds. Please enter an index between 0 and " + (vehicles.length - 1) + ".");
        }

        scanner.close();
    }
}