import java.io.*;
import java.util.*;
public class PingDecorator {
    public static void ping(String url) {
        String cmd = "ping" + url;
        try{
            Runtime rt = Runtime.getRuntime();
            Process p = rt.exec(cmd);
            Scanner sc = new Scanner(p.getInputStream()).useDelimiter("\\Z");
            System.out.println("URL : "+url+" returned " + sc.next());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}