import java.util.Scanner;
public class ValueReader {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a value");
            return;
        }

        int val = Integer.parseInt(args[0]);
        System.out.println("The value is " + val);
    }
}