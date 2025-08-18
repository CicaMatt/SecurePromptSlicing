import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CheckUserId {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java CheckUserId <username>");
            System.exit(1);
        }

        String username = args[0];
        int result = runIdCommand(username);

        if (result == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.err.println("Command execution failed with status code: " + result);
        }
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        try {
            Process process = processBuilder.start();
            StringBuilder output = new StringBuilder();

            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
            }

            System.out.println(output.toString());

            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1;
        }
    }
}