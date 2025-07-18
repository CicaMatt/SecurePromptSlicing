import java.util.*;
import java.io.*;
  public class GetUser {
    public static String runCommand(String cmd) {
        StringBuilder result = new StringBuilder();
        try{
            Process p = Runtime.getRuntime().exec(cmd);
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while((line = br.readLine()) != null) {
                result.append(line + "\n");
            }
        } catch (Exception e){
            System.out.println("Error executing command: " + cmd);
        } 
        return result.toString();
    }
    public static void main(String[] args) {
        if(args.length == 1) {
            String username = args[0];
            String cmd = "cat /etc/passwd | grep " + username;
            System.out.println("Executing command: " + cmd);
            System.out.println(runCommand(cmd));
        } else {
            System.out.println("Usage: java GetUser <username>");
        }
    }
}