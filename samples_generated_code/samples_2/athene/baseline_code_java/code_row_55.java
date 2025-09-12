import java.util.Scanner;

public class Add Thousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            int value = Integer.parseInt(args[0]);
            value += 1000;
            System.out.println(value);
            System.exit(0);
        } else {
            System.out.println("No input provided");
            System.exit(1);
        }
    }
}