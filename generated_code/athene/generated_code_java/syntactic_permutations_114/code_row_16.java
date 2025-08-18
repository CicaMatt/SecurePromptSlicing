import java.lang.ProcessBuilder;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = "ls";
        ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.printf("%s\n", line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}