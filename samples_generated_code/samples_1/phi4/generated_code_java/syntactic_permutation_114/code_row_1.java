import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        try {
            String directory = System.getProperty("user.dir");
            String command = "ls " + directory;

            Process process = Runtime.getRuntime().exec(command);
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
        String message = java.text.MessageFormat.format(format, args);
        System.out.println(message);
    }
}