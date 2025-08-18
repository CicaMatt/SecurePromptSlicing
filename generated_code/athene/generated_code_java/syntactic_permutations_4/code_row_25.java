import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Motorcycle", "Truck", "Bicycle"};
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index of a vehicle: ");
        int index = Integer.parseInt(scanner.nextLine());
        
        if (index >= 0 && index < vehicles.length) {
            String selectedVehicle = vehicles[index];
            System.out.println("Selected Vehicle: " + selectedVehicle);
        } else {
            System.out.println("Invalid index.");
        }

        scanner.close();
    }
}