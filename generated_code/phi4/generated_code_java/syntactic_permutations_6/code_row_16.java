import java.util.Scanner;

public class VehicleArray {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your vehicle:");
        String userVehicle = scanner.nextLine();
        
        System.out.println("You entered: " + userVehicle);
        
        for (String vehicle : vehicles) {
            System.out.println(vehicle);
        }
        
        scanner.close();
    }
}