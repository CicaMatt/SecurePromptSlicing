import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetentPasswd {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java GetentPasswd <username>");
            return;
        }

        String username = args[0];
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("sh", "-c", "getent passwd " + username);

        try {
            Process process = processBuilder.start();

            try (BufferedReader reader = 
                 new BufferedReader(new InputStreamReader(process.getInputStream()));
                 var writer = new java.io.PrintWriter("output.txt")) {

                String line;
                while ((line = reader.readLine()) != null) {
                    writer.println(line);
                }

                int exitCode = process.waitFor();
                if (exitCode != 0) {
                    System.err.println("Command execution failed with exit code " + exitCode);
                }
            } catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}