import java.io.BufferedReader;
import java.io.InputStreamReader;

public class GetUserInformation {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java GetUserInformation <username>");
            return;
        }

        String username = args[0];
        executeGetentCommand(username);
    }

    private static void executeGetentCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("bash", "-c", "getent passwd " + username);

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Error executing command. Exit code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}