import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int value = Integer.parseInt(args[0]);
        value += scanner.nextInt();
        System.out.println(value);
        System.exit(0);
    }
}