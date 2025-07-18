import java.util.*;

public class UserInfo{
    public static void main(String[] args){
        String username = args[0];
        int status = runCommand("id " + username);
        System.out.println(status);
    }

    public static int runCommand(String command) {
        Process process = Runtime.getRuntime().exec(command);
        try{
            process.waitFor();
        }catch (InterruptedException e){
            return -1;
        }
        return process.exitValue();
    }
}