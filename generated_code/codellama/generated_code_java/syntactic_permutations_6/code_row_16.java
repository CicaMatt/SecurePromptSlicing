import java.util.*;
    public class Vehicles {
        public static void main(String[] args) {
            String[] vehicles = {"Toyota", "Honda", "Ford"};
            Scanner scanner = new Scanner(System.in);
            System.out.println("Which vehicle would you like to choose?");
            String userInput = scanner.nextLine();
            if (userInput.equalsIgnoreCase("Toyota")) {
                return "Toyota";
            } else if (userInput.equalsIgnoreCase("Honda")) {
                return "Honda";
            } else if (userInput.equalsIgnoreCase("Ford")) {
                return "Ford";
            } else {
                System.out.println("Not a valid input");
            }
        for(int i = 0; i < vehicles.length; i++) {
            System.out.println(vehicles[i]);
        }
    }
}