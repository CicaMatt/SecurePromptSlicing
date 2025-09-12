import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("Please provide a username as a command line argument.");
            System.exit(1);
        }

        String username = args[0];
        executeCommand(username);
    }

    private static void executeCommand(String username) {
        try {
            Process process = new ProcessBuilder()
                    .command("sh", "-c", "cat /etc/passwd | grep " + username)
                    .start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error executing command. Exit code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}