import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandLineExecutor {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java CommandLineExecutor <command>");
            return;
        }

        String command = "id " + args[0];
        int exitStatus = runCommand(command);

        System.out.println("Exit status: " + exitStatus);
    }

    private static int runCommand(String command) {
        Process process = null;
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader =
                    new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1; // Indicate failure
        } finally {
            if (process != null) {
                try {
                    process.destroy();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }
}