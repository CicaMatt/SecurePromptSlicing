import java.util.Scanner;

public class VehicleIndex {

    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle (0-" + (vehicles.length - 1) + "):");
        
        try {
            int index = scanner.nextInt();
            
            if (index >= 0 && index < vehicles.length) {
                System.out.println("The vehicle at index " + index + " is: " + vehicles[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index.");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}