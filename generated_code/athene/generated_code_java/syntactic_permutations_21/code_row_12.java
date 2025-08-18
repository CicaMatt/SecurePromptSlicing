import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            int value = Integer.parseInt(args[0]);
            value += 1;
            System.out.println(value);
        }
        System.exit(0);
    }
}