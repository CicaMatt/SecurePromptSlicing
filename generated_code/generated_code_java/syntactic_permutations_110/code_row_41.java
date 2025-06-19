import java.io.*;
public class ExitStatus{
    public static void main(String[] args){
        try{
            String username = args[0];
            Process process = Runtime.getRuntime().exec("id " + username);
            int exitStatus = process.waitFor();
            System.out.println("Exit status: "+ exitStatus);
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}