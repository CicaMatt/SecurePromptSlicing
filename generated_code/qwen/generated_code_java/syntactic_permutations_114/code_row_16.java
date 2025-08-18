import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = "ls";
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.format("%s%n", line);
            }
            int exitCode = process.waitFor();
            System.out.format("Exited with code %d%n", exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}