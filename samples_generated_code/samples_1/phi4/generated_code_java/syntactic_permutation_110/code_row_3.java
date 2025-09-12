import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCommand {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: java UserCommand <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("id", username);

        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitValue = process.waitFor();
            return exitValue;

        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}