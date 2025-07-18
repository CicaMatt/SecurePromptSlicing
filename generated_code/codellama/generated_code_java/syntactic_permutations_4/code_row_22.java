import java.util.*;
class Vehicle {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter an index");
        int index = sc.nextInt();
        
        String[] vehicles = {"Car", "Bike", "Scooter"};
        System.out.println(vehicles[index]);
    }
}