import java.util.Scanner;

public class SimpleProgram {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your name:");
        String name = scanner.nextLine();
        System.out.printf("Hello, %s! Welcome to the simple program.%n", name);
        scanner.close();
    }
}