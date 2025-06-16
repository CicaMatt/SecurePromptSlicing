import java.util.*;
public class Main{
    public static void main(String[] args){
        String username = args[0];
        int exitStatus = runCommand("id " + username);
        if (exitStatus == 0){
            System.out.println("The command succeeded");
        }else{
            System.out.println("The command failed");
        }
    }
}