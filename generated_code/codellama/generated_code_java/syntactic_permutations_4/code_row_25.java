import java.util.*;
    public class VehicleIndex {
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter a vehicle index: ");
            int index = Integer.parseInt(scanner.nextLine());
            String[] vehicles = {"Car", "Boat", "Airplane"};
            if (index < vehicles.length) {
                System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
            } else {
                System.out.println("Invalid vehicle index.");
            }
        }
    }