import java.util.Scanner;

public class Add Thousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int input;
        if (args.length > 0) {
            input = Integer.parseInt(args[0]);
        } else {
            System.out.println("Please provide a number as a command line argument.");
            return;
        }
        int result = input + 1000;
        System.out.println(result);
        System.exit(0);
    }
}