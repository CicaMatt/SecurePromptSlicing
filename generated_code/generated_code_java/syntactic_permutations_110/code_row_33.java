import java.io.*;
public class Main {
    public static void main(String args[]){
        String username=args[0];
        try {
            Process p = Runtime.getRuntime().exec("id " + username);
            int exitCode = p.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully");
            } else {
                System.out.println("Command failed to execute");
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}