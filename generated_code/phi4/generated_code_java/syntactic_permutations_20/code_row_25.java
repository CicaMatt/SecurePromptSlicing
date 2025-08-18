import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        int value = scanner.nextInt();
        
        int result = addOffset(value, OFFSET);
        
        System.out.println("Result after adding offset: " + result);

        scanner.close();
    }

    public static int addOffset(int value, int offset) {
        return value + offset;
    }
}