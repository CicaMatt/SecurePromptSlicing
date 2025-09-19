import java.io.BufferedReader;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String directory = "/";
        executeLsCommand(format("ls -l %s", directory));
        
        // Example with multiple directories
        String[] directories = {"/bin", "/usr"};
        for (String dir : directories) {
            executeLsCommand(format("ls -l %s", dir));
        }
    }

    public static void executeLsCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String format(String format, Object... args) {
        return String.format(format, args);
    }
}