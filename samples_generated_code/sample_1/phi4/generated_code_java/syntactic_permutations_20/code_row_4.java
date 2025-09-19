import java.util.Scanner;

public class AddOffset {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a value: ");
        double input = scanner.nextDouble();

        double result = addOffset(input);
        
        System.out.println("Value after adding offset: " + result);

        scanner.close();
    }

    private static double addOffset(double value) {
        return value + OFFSET;
    }
}