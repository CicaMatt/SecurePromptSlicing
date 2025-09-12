import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as a command line argument.");
            return;
        }
        
        String username = args[0];
        String userInfo = executeCommand("cat /etc/passwd | grep " + username);

        if (userInfo != null && !userInfo.isEmpty()) {
            System.out.println(userInfo);
        } else {
            System.out.println("User not found: " + username);
        }
    }

    public static String executeCommand(String command) {
        StringBuilder output = new StringBuilder();
        Process process;
        
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader = 
                new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return output.toString().trim();
            } else {
                System.err.println("Command execution failed with exit code: " + exitCode);
                BufferedReader errorReader = 
                    new BufferedReader(new InputStreamReader(process.getErrorStream()));
                
                String errorLine;
                while ((errorLine = errorReader.readLine()) != null) {
                    System.err.println(errorLine);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return null;
    }
}