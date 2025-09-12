import java.util.Scanner;

public class CommandLineExecutor {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter command:");
        String command = scanner.nextLine();

        executeCommand(command);
        
        scanner.close();
    }

    private static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            System.out.println("Command executed with exit code: " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String format(String format, Object... args) {
        return String.format(format, args);
    }
}