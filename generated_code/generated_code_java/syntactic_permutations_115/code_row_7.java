import java.util.*;
public class Solution {
    public static void main(String[] args) {
        String result = commandLineUtils("ls", "-l");
        System.out.println(result);
    }
    
    public static String commandLineUtils(String... args) {
        StringBuilder sb = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec(args);
            
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = br.readLine()) != null) {
                sb.append(line).append("\n");
            }
            
        } catch (Exception e) {
            System.out.println("Error executing command!");
        }
        return sb.toString();
    }
}