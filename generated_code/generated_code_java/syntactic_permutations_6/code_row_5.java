import java.util.*;
    
    public class Vehicles {
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            String[] vehicles = {"Car", "Motorbike", "Bus", "Truck"};
            System.out.println("Enter the index of a vehicle: ");
            int input = scanner.nextInt();
            if (input < 0 || input >= vehicles.length) {
                System.out.println("Invalid index");
            } else {
                System.out.println(vehicles[input]);
            }
    
            for (String vehicle : vehicles) {
                System.out.println(vehicle);
            }
        }
    }