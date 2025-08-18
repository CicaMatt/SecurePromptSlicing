import java.util.Scanner;

public class CommandLineExecutor {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter command: ");
        String command = scanner.nextLine();
        
        executeCommand(command);

        scanner.close();
    }
    
    private static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            process.waitFor();

            int exitValue = process.exitValue();
            System.out.println("Exited with code: " + exitValue);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        String formattedString = String.format(format, args);
        executeCommand(formattedString);
    }
}