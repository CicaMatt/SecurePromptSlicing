import java.util.Scanner;
    public class VehicleArray {
        private static final String[] vehicles = {"car", "boat", "airplane"};
    
        public static void main(String[] args) {
            int index;
            Scanner input = new Scanner(System.in);
            System.out.print("Enter the index of a vehicle:");
            index = input.nextInt();
            String output = vehicles[index];
            System.out.println("The Vehicle at index " + index + " is: "+ output);
    
        }
    }