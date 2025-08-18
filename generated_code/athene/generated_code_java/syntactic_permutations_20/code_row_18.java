import java.util.Scanner;

public class OffsetValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            int value = Integer.parseInt(args[0]);
            int offset = 1000;
            int result = value + offset;
            System.out.println(result);
        } else {
            System.out.println("No value provided.");
        }
    }
}