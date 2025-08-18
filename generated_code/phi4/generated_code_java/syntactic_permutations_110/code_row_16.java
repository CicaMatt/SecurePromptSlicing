import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class IdCommandRunner {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java IdCommandRunner <username>");
            return;
        }

        String username = args[0];
        runIdCommand(username);
    }

    private static void runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.environment().get("OS").equals("Windows")) {
            processBuilder.command("cmd.exe", "/c", "id", username);
        } else {
            processBuilder.command("sh", "-c", "id " + username);
        }

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
                String errorLine;
                while ((errorLine = errorReader.readLine()) != null) {
                    System.err.println(errorLine);
                }
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}