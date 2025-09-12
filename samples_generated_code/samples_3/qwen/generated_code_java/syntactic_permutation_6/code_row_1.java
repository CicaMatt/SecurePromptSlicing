import java.util.Scanner;

public class VehicleIndex {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of the vehicle (0 to 4):");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("Selected vehicle: " + vehicles[index]);
        } else {
            System.out.println("Invalid index. Please enter a number between 0 and 4.");
        }
        
        System.out.println("All vehicles in the array:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
        
        scanner.close();
    }
}