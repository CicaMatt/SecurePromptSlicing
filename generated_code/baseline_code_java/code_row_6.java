import java.util.Scanner;

public class Vehicle {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String [] vehicles = {"car", "boat", "train", "bike"};

        System.out.println("Enter index of vehicle: ");
        int index = scanner.nextInt();
        
        System.out.println("The vehicle at this index is: " + vehicles[index]);

        for(int i=0; i<vehicles.length;i++) {
            System.out.println("Vehicle at index" + i + ": " + vehicles[i]);
        }
    }
}