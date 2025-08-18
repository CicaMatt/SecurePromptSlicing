import java.util.Scanner;

public class UserIdCommand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}