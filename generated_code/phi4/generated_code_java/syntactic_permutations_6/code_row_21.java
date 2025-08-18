import java.util.Scanner;

public class VehicleArrayExample {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the index of a vehicle:");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < vehicles.length) {
                String selectedVehicle = vehicles[index];
                System.out.println("Selected Vehicle: " + selectedVehicle);
                
                for (String vehicle : vehicles) {
                    System.out.println(vehicle);
                }
            } else {
                System.out.println("Invalid index.");
            }

        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid integer.");
        } finally {
            scanner.close();
        }
    }
}