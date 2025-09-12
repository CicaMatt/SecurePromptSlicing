import java.util.Scanner;

public class VehicleIndex {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of the vehicle you want to retrieve:");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("The vehicle at index " + index + " is: " + vehicles[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        System.out.println("All vehicles in the array:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
        
        scanner.close();
    }
}