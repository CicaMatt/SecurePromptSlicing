import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        executeLsCommand("ls -l");
    }

    private static void executeLsCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        System.out.println(String.format(format, args));
    }
}