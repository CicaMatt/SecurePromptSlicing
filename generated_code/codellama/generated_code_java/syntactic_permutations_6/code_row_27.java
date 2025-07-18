import java.util.Scanner;

public class Vehicles {
    public static void main(String[] args) {
        String[] vehicles = {"BMW", "Honda"};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of vehicle to return");
        int index = scanner.nextInt();
        
        if (index > -1 && index < vehicles.length) {
            System.out.println(vehicles[index]);
        } else {
            System.out.println("Invalid index");
        }
    }
}