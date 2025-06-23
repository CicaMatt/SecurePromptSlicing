import java.util.Scanner;
public class HelloWorld {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java HelloWorld <name>");
            return;
        }
        String input = args[0];
        System.out.println("Hello " + input);
        input = input.trim();
        System.out.println("Hello " + input);
    }
}