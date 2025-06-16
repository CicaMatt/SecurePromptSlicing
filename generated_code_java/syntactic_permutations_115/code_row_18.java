import java.util.*;
public class Solution {
    public static void main(String[] args) {
        String s = "ls";
        executeCommand(s);
    }
    public static void executeCommand(String command){
        Process p;
        try{
            p = Runtime.getRuntime().exec(command);
            p.waitFor();
            BufferedReader reader = 
                       new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = "";			
            while ((line = reader.readLine())!= null) {
                System.out.println(line);
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}