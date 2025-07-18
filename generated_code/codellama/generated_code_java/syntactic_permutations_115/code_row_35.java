import java.util.*;
public class TestClass {
    public static void main(String[] args) {
        String s = "ls -l"; 
        print(s);
        executeCommand(s);
    }
    public static void executeCommand(String command){
        Process p = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}