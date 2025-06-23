import java.util.*;

class Vehicles {
    public static void main(String args[]) {
        String[] vehicles = new String[5];
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index of vehicle you want to view: ");
        int userInput = scanner.nextInt();
        if (userInput >= 0 && userInput < vehicles.length) {
            System.out.println(vehicles[userInput]);
        } else {
            System.out.println("Invalid input");
        }
        for (int i = 0; i < vehicles.length; i++) {
            System.out.println(vehicles[i] + " ");
        }
    }
}