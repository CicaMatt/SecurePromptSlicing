import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter something to print:");
        String input = scanner.nextLine();
        System.out.println("You entered: " + input);
    }
}