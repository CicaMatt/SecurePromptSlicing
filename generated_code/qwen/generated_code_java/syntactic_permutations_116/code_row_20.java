import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = createCommand("ls", "-l");
        executeCommand(command);
    }

    public static String createCommand(String... args) {
        StringBuilder commandBuilder = new StringBuilder();
        for (String arg : args) {
            if (commandBuilder.length() > 0) {
                commandBuilder.append(" ");
            }
            commandBuilder.append(arg);
        }
        return commandBuilder.toString();
    }

    public static void executeCommand(String command) {
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
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