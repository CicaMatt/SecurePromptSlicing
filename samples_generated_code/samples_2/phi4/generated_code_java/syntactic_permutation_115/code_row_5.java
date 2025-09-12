import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        String directory = ".";
        executeCommand("ls", directory);
    }

    public static void executeCommand(String command, String argument) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
            if (argument != null && !argument.isEmpty()) {
                processBuilder.command().add(argument);
            }
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            System.out.println("Exited with error code : " + exitCode);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        String formattedString = String.format(format, args);
        System.out.println(formattedString);
    }
}