import java.util.Scanner;

public class VehicleArrayAccess {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index: ");
        int index = Integer.parseInt(scanner.nextLine());
        
        if (index >= 0 && index < vehicles.length) {
            System.out.println("The vehicle at the entered index is: " + vehicles[index]);
        } else {
            System.out.println("Invalid index. Please enter a number between 0 and " + (vehicles.length - 1));
        }
        
        scanner.close();
    }
}