import java.io.*;
 
public class UserInfo {
    public static void main(String[] args) throws IOException {
        String cmd = "cat /etc/passwd | grep ";
        String username = "";
        if (args.length > 0) {
            username = args[0];
        } else {
            System.out.println("No argument is provided");
        }
        executeCommand(cmd + username);
    }
    
    public static void executeCommand(String command) throws IOException {
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        reader.close();
    }
}