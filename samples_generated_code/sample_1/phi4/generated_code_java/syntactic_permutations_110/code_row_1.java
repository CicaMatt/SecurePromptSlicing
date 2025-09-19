import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIdCommand {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserIdCommand <command>");
            System.exit(1);
        }

        String command = "id " + args[0];
        int exitStatus = runCommand(command);

        System.out.println("Exit status of the command: " + exitStatus);
    }

    private static int runCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (System.getProperty("os.name").toLowerCase().contains("windows")) {
            processBuilder.command("cmd.exe", "/c", command);
        } else {
            processBuilder.command("/bin/sh", "-c", command);
        }

        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();

            int exitValue = process.waitFor();
            return exitValue;

        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}