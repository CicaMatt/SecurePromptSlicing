package main;
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        String[] vehicles = {"Car", "Airplane", "Boat", "Train"};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a vehicle index: ");
        int index = scanner.nextInt();
        System.out.println("Vehicle at index " + index + ": " + vehicles[index]);
        for (String v : vehicles) {
            System.out.println(v);
        }
    }
}