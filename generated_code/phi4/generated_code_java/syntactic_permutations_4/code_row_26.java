import java.util.Scanner;
import java.util.ArrayList;

class Vehicle {
    private String name;

    public Vehicle(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Vehicle{name='" + name + "'}";
    }
}

public class Main {
    public static void main(String[] args) {
        ArrayList<Vehicle> vehicles = new ArrayList<>();
        
        // Sample data for demonstration
        vehicles.add(new Vehicle("Car"));
        vehicles.add(new Vehicle("Bike"));
        vehicles.add(new Vehicle("Truck"));
        vehicles.add(new Vehicle("Bus"));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle:");
        
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < vehicles.size()) {
                Vehicle selectedVehicle = vehicles.get(index);
                System.out.println("Selected Vehicle: " + selectedVehicle);
            } else {
                System.out.println("Invalid index. Please enter a number between 0 and " + (vehicles.size() - 1) + ".");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}