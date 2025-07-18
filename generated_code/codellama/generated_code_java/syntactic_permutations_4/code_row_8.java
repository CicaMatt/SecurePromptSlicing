import java.util.Scanner;
public class Vehicle {
    public static void main(String[] args) {
        System.out.print("Enter a index ");
        Scanner input = new Scanner(System.in);
        int index = Integer.parseInt(input.nextLine());
        String[] vehicles = {"car", "bus", "truck"};
        System.out.println("The vehicle at the index "+vehicles[index]+".");
    }
}