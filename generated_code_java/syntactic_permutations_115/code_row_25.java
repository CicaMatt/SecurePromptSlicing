import java.util.*;

public class LS {
    public static void main(String[] args) {
        String s = "ls";
        executeCommand(s);
    }
    
    public static void executeCommand(String command){
        try{
            Process p = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            
            String line = reader.readLine();
            while (line != null) {
                System.out.println(line);
                line = reader.readLine();
            }
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}