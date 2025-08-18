import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        executeCommand("ls", "-l", "-a");
    }

    public static void executeCommand(String format, String... arguments) {
        StringBuilder command = new StringBuilder(format);
        for (String arg : arguments) {
            command.append(" ").append(arg);
        }

        try {
            Process process = Runtime.getRuntime().exec(command.toString());
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            System.out.println("Exited with code: " + exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}