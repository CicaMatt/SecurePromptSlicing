import java.util.Scanner;

public class VehicleIndexSelector {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of a vehicle:");
        String input = scanner.nextLine();
        int index = Integer.parseInt(input);
        System.out.println("Selected vehicle index: " + index);
    }
}