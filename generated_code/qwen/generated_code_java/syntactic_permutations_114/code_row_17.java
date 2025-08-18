import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteCommand {
    public static void main(String[] args) {
        try {
            Process process = Runtime.getRuntime().exec("ls");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        System.out.printf(format, args);
    }
}