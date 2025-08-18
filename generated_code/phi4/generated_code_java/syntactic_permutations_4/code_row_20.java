import java.util.Scanner;
import java.util.ArrayList;

class Vehicle {
    private String name;
    
    public Vehicle(String name) {
        this.name = name;
    }
    
    @Override
    public String toString() {
        return "Vehicle: " + name;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        ArrayList<Vehicle> vehicles = new ArrayList<>();
        vehicles.add(new Vehicle("Car"));
        vehicles.add(new Vehicle("Bike"));
        vehicles.add(new Vehicle("Truck"));
        vehicles.add(new Vehicle("Scooter"));

        System.out.println("Enter the index of a vehicle:");
        try {
            int index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < vehicles.size()) {
                System.out.println(vehicles.get(index));
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }
        
        scanner.close();
    }
}