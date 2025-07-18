import java.util.Scanner;

public class Solution {
    
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Username: ");
        String username = sc.nextLine();
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status of id command: " + exitStatus);
    }
    
    public static int runIdCommand(String username) {
        
        try {
            Process proc = Runtime.getRuntime().exec("id " + username);
            proc.waitFor();
            
            return proc.exitValue();
            
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return 1;
        }
    }
}