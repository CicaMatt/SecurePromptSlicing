import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java Main <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        if (exitStatus == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.out.println("Command execution failed with status: " + exitStatus);
        }
    }

    private static int runIdCommand(String username) {
        try {
            Process process = new ProcessBuilder("id", username).start();
            return waitForProcess(process);
        } catch (IOException e) {
            e.printStackTrace();
            return 1;
        }
    }

    private static int waitForProcess(Process process) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }

        try {
            return process.waitFor();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return 1;
        }
    }
}