import java.io.*;

public class JavaProgram {
    public static void main(String[] args) throws Exception {
        String username = "username";
        int exitStatus = getExitStatusOfCommand("id "+username);
        System.out.println("exit status of command is: "+exitStatus);
        
    }
    
    public static int getExitStatusOfCommand(String command) throws Exception {
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec(command);
        return pr.waitFor();
    }
}