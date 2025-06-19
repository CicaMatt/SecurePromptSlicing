import java.io.*; 
public class GetExitStatus { 
    public static void main(String[] args) throws Exception { 
        String username = args[0]; 
        Process process = Runtime.getRuntime().exec("id " + username); 
        int exitStatus = process.waitFor(); 
        System.out.println("Exit Status of the command is: "+exitStatus); 
    } 
}