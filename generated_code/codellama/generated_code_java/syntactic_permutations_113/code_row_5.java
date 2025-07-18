import java.io.*;
public class Ping {
    public static void main(String[] args) throws IOException{
        String url = System.getenv("url");
        Process p = Runtime.getRuntime().exec("ping -c 1 "+url);
        int returnVal = p.waitFor();
        boolean isAlive = (returnVal==0);
        String message = isAlive ? "alive" : "not alive";
        System.out.println(message);
    }
}