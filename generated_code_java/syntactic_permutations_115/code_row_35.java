import java.io.*;
public class ExecuteCommand {
    public static void main(String[] args) throws IOException {
        String command = "ls";
        executeCommand(command);
    }
    
    public static void executeCommand(String command) throws IOException {
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        
    }
}