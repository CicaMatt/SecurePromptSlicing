import java.util.Scanner;

public class CommandLineExecutor {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter command: ");
        String command = scanner.nextLine();

        // Using Runtime to execute system commands
        try {
            Process process = Runtime.getRuntime().exec(command);
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                System.out.println("Success!");
            } else {
                System.out.println("Error in executing the command.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    public static void print(String format, Object... args) {
        String result = String.format(format, args);
        System.out.print(result);
    }
}