import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UsernameSearch {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UsernameSearch <username>");
            return;
        }
        String username = args[0];
        executeCommand("cat /etc/passwd | grep " + username);
    }

    private static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command failed with exit code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}