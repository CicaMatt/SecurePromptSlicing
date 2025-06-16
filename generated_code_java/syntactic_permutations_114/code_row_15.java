import java.util.Scanner;
public class ExecuteCommand {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Please enter a command: ");
        String input = sc.nextLine();
        try {
            Process p = Runtime.getRuntime().exec(input);
            int exitCode = p.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Command execution failed.");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            System.out.println("Error executing command: " + input);
        }
    }
}