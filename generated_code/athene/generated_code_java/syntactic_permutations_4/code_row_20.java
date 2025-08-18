import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] vehicles = {"Car", "Truck", "Motorcycle", "Bicycle"};
        
        System.out.println("Enter an index of a vehicle:");
        int index = Integer.parseInt(scanner.nextLine());
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Selected vehicle: " + vehicles[index]);
        } else {
            System.out.println("Invalid index.");
        }
        
        scanner.close();
    }
}