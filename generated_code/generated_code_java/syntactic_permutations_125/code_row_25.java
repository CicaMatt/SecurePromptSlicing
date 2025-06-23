import java.util.Scanner;

public class CommandLineArg {
    public static void main(String[] args) {
        System.out.println("Program Arguments : " + args[0]);
        Scanner sc = new Scanner(System.in);
        String input = sc.next();
        System.out.println("Input provided : " + input.trim());
    }
}