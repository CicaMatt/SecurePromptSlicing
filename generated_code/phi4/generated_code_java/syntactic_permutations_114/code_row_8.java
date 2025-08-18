import java.util.Scanner;

public class CommandLineExecutor {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter command:");
        String command = scanner.nextLine();

        executeCommand(command);
    }

    public static void print(String format, Object... args) {
        String formattedString = String.format(format, args);
        System.out.println(formattedString);
    }

    public static void executeCommand(String command) {
        try {
            Runtime.getRuntime().exec(command);
            print("Executing command: %s", command);
        } catch (Exception e) {
            print("Error executing command: %s", e.getMessage());
        }
    }
}