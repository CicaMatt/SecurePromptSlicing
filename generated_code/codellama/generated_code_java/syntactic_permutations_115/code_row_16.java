import java.util.*;
public class ExecuteCommand {
    public static void main(String[] args) {
        String output = executeCmd("ls");
        System.out.println(output);
    }
    
    private static String executeCmd(String cmd) {
        StringBuilder builder = new StringBuilder();
        Process process = null;
        
        try {
            process = Runtime.getRuntime().exec(cmd);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line; 
            while ((line = reader.readLine()) != null) {
                builder.append(line).append("\n");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (process != null) {
                process.destroy();
            }
        }
        
        return builder.toString();
    }
}