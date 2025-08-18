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
        Scanner scanner = new Scanner(System.in);
        
        Vehicle[] vehicles = {
            new Vehicle("Car"),
            new Vehicle("Bicycle"),
            new Vehicle("Motorcycle"),
            new Vehicle("Truck")
        };
        
        System.out.println("Enter the index of a vehicle (0 to " + (vehicles.length - 1) + "): ");
        int index;
        try {
            index = scanner.nextInt();
            
            if (index >= 0 && index < vehicles.length) {
                System.out.println("The vehicle at index " + index + " is: " + vehicles[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index.");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}