import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus"};
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter a vehicle:");
        String selectedVehicle = scanner.nextLine();
        
        for (String vehicle : vehicles) {
            if (vehicle.equalsIgnoreCase(selectedVehicle)) {
                System.out.println("Selected: " + vehicle);
            }
            System.out.println(vehicle);
        }

        scanner.close();
    }
}