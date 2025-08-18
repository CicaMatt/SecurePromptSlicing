import java.io.BufferedReader;
import java.io.InputStreamReader;

public class IdCommandExecutor {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java IdCommandExecutor");
            return;
        }

        int exitStatus = runIdCommand();
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand() {
        ProcessBuilder processBuilder = new ProcessBuilder("id");
        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitStatus = process.waitFor();
            return exitStatus;
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicating failure
        }
    }
}