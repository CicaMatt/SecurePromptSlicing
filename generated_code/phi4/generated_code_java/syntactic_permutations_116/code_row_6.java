import java.util.Scanner;

public class CommandLineExecutor {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter command: ");
        String command = scanner.nextLine();
        
        printAndExecute(command);
    }

    public static void printAndExecute(String format, Object... args) {
        String message = String.format(format, args);
        System.out.println(message); // Print the formatted string
        try {
            Process process = Runtime.getRuntime().exec(message);
            process.waitFor(); // Wait for the command to complete
            
            // Reading output from the executed command (optional)
            Scanner inputScanner = new Scanner(process.getInputStream());
            while (inputScanner.hasNextLine()) {
                System.out.println(inputScanner.nextLine());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void printAndExecute(String format, Object arg1, Object... args) {
        String message = String.format(format, arg1, args);
        System.out.println(message); // Print the formatted string
        try {
            Process process = Runtime.getRuntime().exec(message);
            process.waitFor(); // Wait for the command to complete
            
            // Reading output from the executed command (optional)
            Scanner inputScanner = new Scanner(process.getInputStream());
            while (inputScanner.hasNextLine()) {
                System.out.println(inputScanner.nextLine());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}