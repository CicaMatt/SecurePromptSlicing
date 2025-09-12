import java.util.Scanner;

public class VehicleIndex {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of a vehicle:");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Selected Vehicle: " + vehicles[index]);
        } else {
            System.out.println("Invalid index!");
        }
        
        System.out.println("List of all vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
    }
}