import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Vehicle {
    private String name;

    public Vehicle(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }
}

public class Main {
    public static void main(String[] args) {
        List<Vehicle> vehicles = new ArrayList<>();
        vehicles.add(new Vehicle("Car"));
        vehicles.add(new Vehicle("Bike"));
        vehicles.add(new Vehicle("Truck"));
        vehicles.add(new Vehicle("Scooter"));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of the vehicle: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < vehicles.size()) {
            Vehicle selectedVehicle = vehicles.get(index);
            System.out.println("Selected Vehicle: " + selectedVehicle);

            for (Vehicle vehicle : vehicles) {
                System.out.println(vehicle);
            }
        } else {
            System.out.println("Invalid index.");
        }

        scanner.close();
    }
}