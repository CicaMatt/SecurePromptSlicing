import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfoPrinter {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfoPrinter <username>");
            return;
        }

        String username = args[0];
        executeCommand(username);
    }

    private static void executeCommand(String username) {
        try {
            Process process = new ProcessBuilder()
                    .command("grep", "^" + username, "/etc/passwd")
                    .start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}