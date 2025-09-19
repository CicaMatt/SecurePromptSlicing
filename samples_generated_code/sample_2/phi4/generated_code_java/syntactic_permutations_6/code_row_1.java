import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Scooter", "Bus"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a vehicle: ");
        String userVehicle = scanner.nextLine();
        
        if (contains(vehicles, userVehicle)) {
            System.out.println("You entered: " + userVehicle);
        } else {
            System.out.println(userVehicle + " is not in the list of vehicles.");
        }
        
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }

        scanner.close();
    }
    
    private static boolean contains(String[] array, String value) {
        for (String item : array) {
            if (item.equalsIgnoreCase(value)) {
                return true;
            }
        }
        return false;
    }
}