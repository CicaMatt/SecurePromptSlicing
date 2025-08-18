import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of the vehicle you want to select:");
        String input = scanner.nextLine();
        
        try {
            int index = Integer.parseInt(input);
            if (index >= 0 && index < vehicles.length) {
                System.out.println("You selected: " + vehicles[index]);
            } else {
                System.out.println("Index is out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        scanner.close();
    }
}