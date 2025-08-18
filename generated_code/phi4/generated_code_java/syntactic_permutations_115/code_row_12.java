import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandLineExecutor {

    public static void main(String[] args) {
        String result = executeCommand("ls");
        System.out.println(result);
        
        String formattedCommand = createFormattedString("%s -l", "ls");
        result = executeCommand(formattedCommand);
        System.out.println(result);
    }

    public static String executeCommand(String command) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = 
                new BufferedReader(new InputStreamReader(process.getInputStream()));
                
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                System.out.println("Success!");
            } else {
                System.err.println("Error in executing command");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return output.toString();
    }

    public static String createFormattedString(String format, Object... args) {
        return String.format(format, args);
    }
}