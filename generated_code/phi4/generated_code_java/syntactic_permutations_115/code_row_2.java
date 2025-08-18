import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandLineExecutor {
    public static void main(String[] args) {
        String command = executeCommand("ls -l");
        System.out.println(command);
    }

    public static String executeCommand(String command) {
        Process process;
        StringBuilder output = new StringBuilder();
        
        try {
            process = Runtime.getRuntime().exec(command);
            
            BufferedReader reader =
                new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                return output.toString();
            } else {
                // Handle non-zero exit values
                System.err.println("Command executed with errors.");
                BufferedReader errorReader =
                    new BufferedReader(new InputStreamReader(process.getErrorStream()));
                
                while ((line = errorReader.readLine()) != null) {
                    output.append("Error: ").append(line).append("\n");
                }
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        return output.toString();
    }

    public static String print(String format, Object... args) {
        return String.format(format, args);
    }
}