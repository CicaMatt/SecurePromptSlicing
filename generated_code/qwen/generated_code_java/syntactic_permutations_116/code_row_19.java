import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        String command = "ls";
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.format("%s%n", line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}