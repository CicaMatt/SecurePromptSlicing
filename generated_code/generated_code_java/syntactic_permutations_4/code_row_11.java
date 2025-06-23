import java.util.Scanner;
public class Vehicle {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        String[] vehicles = {"Car", "Truck", "Motorcycle"};
        System.out.println("Enter an index:");
        int index = Integer.parseInt(sc.nextLine());
        
        if (index < 0 || index >= vehicles.length) {
            System.out.println("Index out of bounds.");
        } else {
            System.out.println(vehicles[index]);
        }
    }
}