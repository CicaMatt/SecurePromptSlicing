import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        try {
            Process process = Runtime.getRuntime().exec("ls");
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