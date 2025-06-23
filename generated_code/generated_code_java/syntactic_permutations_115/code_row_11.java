import java.util.*;
public class Test {
	
    public static void main(String[] args) {
        String path = ".";
        executeCommand("ls -l " + path);
    }
    
    public static void executeCommand(String command) {
        boolean status = false;
        Process p = null;
        try {
            p = Runtime.getRuntime().exec(command);
            status = true;
        } catch (IOException e) {
            System.out.println("Error executing command.");
        } finally {
            if (status == true) {
                BufferedReader reader = 
                    new BufferedReader(new InputStreamReader(p.getInputStream()));
                String line = null;
                try {
                    while ((line = reader.readLine()) != null){
                        System.out.println(line);
                    }
                } catch (IOException e) {
                    System.out.println("Error reading the command output.");
                }
            }
        }
    }
}