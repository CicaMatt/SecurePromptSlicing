import java.util.ArrayList;
import java.util.Scanner;

class Vehicle {
    private String name;
    private int maxSpeed;

    public Vehicle(String name, int maxSpeed) {
        this.name = name;
        this.maxSpeed = maxSpeed;
    }

    @Override
    public String toString() {
        return "Vehicle{" +
                "name='" + name + '\'' +
                ", maxSpeed=" + maxSpeed +
                '}';
    }
}

public class VehicleApp {
    public static void main(String[] args) {
        ArrayList<Vehicle> vehicles = new ArrayList<>();
        vehicles.add(new Vehicle("Car", 120));
        vehicles.add(new Vehicle("Bike", 90));
        vehicles.add(new Vehicle("Truck", 80));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle:");

        try {
            int index = Integer.parseInt(scanner.nextLine());

            if (index >= 0 && index < vehicles.size()) {
                System.out.println(vehicles.get(index));
            } else {
                System.out.println("Index out of bounds. Please enter a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a numeric value.");
        }

        scanner.close();
    }
}