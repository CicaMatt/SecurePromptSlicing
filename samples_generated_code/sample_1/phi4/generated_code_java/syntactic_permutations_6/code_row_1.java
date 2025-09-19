import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Boat"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your vehicle:");
        String userVehicle = scanner.nextLine();
        
        boolean found = false;
        for (String vehicle : vehicles) {
            if (vehicle.equalsIgnoreCase(userVehicle)) {
                found = true;
            }
            System.out.println(vehicle);
        }
        
        if (!found) {
            System.out.println("The entered vehicle is not in the array.");
        }

        scanner.close();
    }
}