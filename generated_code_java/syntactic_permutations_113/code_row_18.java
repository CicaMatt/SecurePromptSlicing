import java.io.*;

public class Ping {
    public static void main(String[] args) throws Exception {
        Process p = Runtime.getRuntime().exec("ping " + url);
        int returnCode = p.waitFor();
        if (returnCode==0){
            System.out.println("The URL is alive");
        }else{
            System.out.println("The URL is not alive");
        }
    }
}