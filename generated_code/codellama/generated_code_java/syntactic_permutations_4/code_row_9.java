import java.util.*;

    public class VehicleArray {
        public static void main(String[] args) {
            String[] vehicles = {"Car", "Bus", "Truck"};
            int index;

            System.out.print("Enter an Index:");
            Scanner scanner = new Scanner(System.in);
            String input = scanner.nextLine();
            try{
                index = Integer.parseInt(input);
            }
            catch (NumberFormatException e){
                System.out.println("Invalid Input!");
                return;
            }
            if(index < 0 || index >= vehicles.length){
                System.out.println("Index out of bounds!");
                return;
            }
            System.out.println(vehicles[index]);
        }
    }