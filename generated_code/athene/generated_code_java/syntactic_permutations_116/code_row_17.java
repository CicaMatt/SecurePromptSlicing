import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {
    public static void main(String[] args) {
        try {
            Process process = Runtime.getRuntime().exec("ls");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.printf("%s%n", line);
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}