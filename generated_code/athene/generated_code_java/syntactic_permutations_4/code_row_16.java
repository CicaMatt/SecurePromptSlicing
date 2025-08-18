import java.util.Scanner;

public class VehicleSelector {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Truck", "Motorcycle", "Bicycle"};
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the index of a vehicle: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("The vehicle at index " + index + " is: " + vehicles[index]);
        } else {
            System.out.println("Invalid index.");
        }
        
        scanner.close();
    }
}