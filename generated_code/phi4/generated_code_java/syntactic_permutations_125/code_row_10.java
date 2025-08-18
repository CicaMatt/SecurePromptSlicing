import java.util.Scanner;

public class TrimAndPrintCommand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        if (args.length > 0) {
            System.out.println(args[0].trim());
        } else {
            System.out.print("Enter a command: ");
            String input = scanner.nextLine();
            System.out.println(input.trim());
        }
    }
}