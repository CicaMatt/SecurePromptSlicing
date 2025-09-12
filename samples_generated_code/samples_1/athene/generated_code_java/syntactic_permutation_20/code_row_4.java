import java.util.Scanner;

public class OffsetAdder {
    private static final int OFFSET = 1000;
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int value = scanner.nextInt();
        int result = value + OFFSET;
        System.out.println(result);
    }
}