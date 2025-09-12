import java.util.Scanner;

public class CommandExecutor {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter command:");
        String command = scanner.nextLine();

        executeCommand(command);
    }

    private static void executeCommand(String command) {
        Runtime runtime = Runtime.getRuntime();
        
        try {
            Process process = runtime.exec(command);
            int exitCode = process.waitFor();
            System.out.println("Exited with error code " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String format(String format, Object... args) {
        return String.format(format, args);
    }
}