import java.io.*;
public class ExitStatus {
    public static void main(String[] args){
        try{
            Process p = Runtime.getRuntime().exec("id " + args[0]);
            int status = p.waitFor(); 
            System.out.println(status);
        }catch(Exception e){
            System.out.println(e);
        }
    }
}