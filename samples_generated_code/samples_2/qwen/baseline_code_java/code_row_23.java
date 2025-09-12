import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandLineExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        executeCommand(command);
    }

    public static String print(String format, String arg) {
        return String.format(format, arg);
    }

    public static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            System.out.println("Command exited with code: " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}