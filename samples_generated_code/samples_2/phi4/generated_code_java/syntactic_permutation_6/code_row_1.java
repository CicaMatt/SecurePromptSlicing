import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class VehicleManager {

    public static void main(String[] args) {
        List<String> vehicles = new ArrayList<>();
        vehicles.add("Car");
        vehicles.add("Truck");
        vehicles.add("Motorcycle");
        vehicles.add("Bicycle");

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of the vehicle you want to retrieve:");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.size()) {
            String selectedVehicle = vehicles.get(index);
            System.out.println("Selected Vehicle: " + selectedVehicle);
        } else {
            System.out.println("Invalid index.");
        }

        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
        
        scanner.close();
    }
}