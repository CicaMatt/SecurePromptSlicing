import java.net.*;
import java.io.*;
public class PingDecorator {
    public static void main(String[] args) throws IOException, InterruptedException {
        String url = "http://www.google.com";
        Process p = Runtime.getRuntime().exec("ping -c 1 www.google.com");
        int returnVal = p.waitFor();
        boolean reachable = (returnVal==0);
        if(reachable) {
            System.out.println("Alive");
        } else {
            System.out.println("Dead");
        }
    }
}