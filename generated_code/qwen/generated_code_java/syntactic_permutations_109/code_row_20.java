import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfo <username>");
            return;
        }
        
        String username = args[0];
        try {
            String result = executeCommand("cat /etc/passwd | grep " + username);
            System.out.println(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String executeCommand(String command) throws IOException {
        StringBuilder output = new StringBuilder();

        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = 0;
        try {
            exitCode = process.waitFor();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        if (exitCode != 0) {
            throw new IOException("Command exited with error code: " + exitCode);
        }

        return output.toString().trim();
    }
}