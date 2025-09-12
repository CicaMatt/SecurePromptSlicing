import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Truck", "Bike", "Scooter"};
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the index of a vehicle:");
        int index = Integer.parseInt(scanner.nextLine());
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Selected vehicle: " + vehicles[index]);
        } else {
            System.out.println("Invalid index.");
        }
        
        scanner.close();
    }
}