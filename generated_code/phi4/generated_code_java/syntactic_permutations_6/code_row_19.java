import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Scooter", "Bus"};
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Choose the index of a vehicle from the list:");
        
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(i + ": " + vehicles[i]);
        }
        
        int index;
        try {
            index = scanner.nextInt();
            
            if (index >= 0 && index < vehicles.length) {
                System.out.println("Selected vehicle: " + vehicles[index]);
            } else {
                System.out.println("Invalid index. Please choose an index between 0 and " 
                                  + (vehicles.length - 1));
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a number.");
        }

        scanner.close();
        
        System.out.println("\nAll vehicles:");
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
    }
}