import java.util.*;
public class Vehicles {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String[] vehicles = {"Car", "Bicycle", "Boat", "Airplane"};
        System.out.println("Please enter the index of a vehicle: ");
        int userInput = sc.nextInt();
        System.out.println("You have entered: " + vehicles[userInput]);
        for (String s : vehicles) {
            System.out.print(s + ", ");
        }
    }
}