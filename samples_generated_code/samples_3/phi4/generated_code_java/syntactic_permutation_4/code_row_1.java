import java.util.Scanner;

public class VehicleSelector {

    public static void main(String[] args) {
        String[] vehicles = {"Car", "Bike", "Truck", "Bus", "Scooter"};

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the index of a vehicle: ");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < vehicles.length) {
                System.out.println("The selected vehicle is: " + vehicles[index]);
            } else {
                System.out.println("Invalid index. Please enter an index between 0 and " 
                                   + (vehicles.length - 1) + ".");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        scanner.close();
    }
}