import java.util.Scanner;

public class AddThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter a number: ");
        if (scanner.hasNextInt()) {
            int value = scanner.nextInt();
            int result = value + 1000;
            System.out.println(result);
        } else {
            System.out.println("Invalid input. Please enter an integer.");
        }
        
        System.exit(0);
    }
}