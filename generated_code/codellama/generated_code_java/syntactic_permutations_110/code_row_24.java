import java.io.*;
public class ExitStatus{
    public static void main(String[] args){
        String username = args[0];
        try{
            Process p = Runtime.getRuntime().exec("id "+username);
            int exitstatus=p.waitFor();
            System.out.println(exitstatus);
        }
        catch (Exception e){}
    }
}