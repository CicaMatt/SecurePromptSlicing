import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandRunner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.exit(1);
        }
        String username = args[0];
        String command = "id " + username;
        ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
        int exitStatus = -1;
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            while (reader.readLine() != null) {
                // Read output, but do nothing with it
            }
            exitStatus = process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println(exitStatus);
    }
}