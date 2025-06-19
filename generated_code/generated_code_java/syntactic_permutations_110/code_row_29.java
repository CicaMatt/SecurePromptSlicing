import java.io.*; 

public class UserId {
    public static void main(String[] args) throws IOException { 
        String username = args[0]; 

        Process p = Runtime.getRuntime().exec("id " + username); 

        int returnValue = p.waitFor(); 

        System.out.println(returnValue);
    }
}