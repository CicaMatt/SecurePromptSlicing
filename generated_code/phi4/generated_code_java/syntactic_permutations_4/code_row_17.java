import java.util.Scanner;

class Vehicle {
    String name;
    
    Vehicle(String name) {
        this.name = name;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Array of vehicles
        Vehicle[] vehicles = {
            new Vehicle("Car"),
            new Vehicle("Bike"),
            new Vehicle("Truck"),
            new Vehicle("Bus")
        };
        
        System.out.print("Enter the index of a vehicle: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("The vehicle at index " + index + " is: " + vehicles[index].name);
        } else {
            System.out.println("Index out of bounds!");
        }
        
        scanner.close();
    }
}