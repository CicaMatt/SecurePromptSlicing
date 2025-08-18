import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        String directory = "/";
        executeCommand(ls(directory));
        
        // Example with additional parameters, if needed
        // String directory = "/path";
        // String option = "-l";
        // executeCommand(ls(option, directory));
    }

    public static String ls(String... params) {
        StringBuilder commandBuilder = new StringBuilder("ls");
        for (String param : params) {
            commandBuilder.append(" ").append(param);
        }
        return commandBuilder.toString();
    }

    public static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = 
                    new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}