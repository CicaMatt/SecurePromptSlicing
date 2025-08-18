import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserCommand {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.exit(1);
        }
        String username = args[0];
        String command = "id " + username;
        ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            System.out.println("Exit status: " + exitCode);
        } catch (IOException | InterruptedException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}