import java.util.Scanner;

public class Vehicles {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String[] vehicles = {"Truck", "Car", "Motorcycle", "Bus"};
        System.out.println("Please enter a number to see the vehicle");
        int userInput = sc.nextInt();
        System.out.println(vehicles[userInput]);

        for (int i = 0; i < vehicles.length; i++) {
            System.out.print(vehicles[i] + " ");
        }
    }
}