import java.io.*;
import java.net.*;
public class Ping {
    public static void main(String[] args) throws Exception {
        URL url = new URL("http://www.example.com");
        String cmd = "ping";
        Process p = Runtime.getRuntime().exec(cmd +" "+url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            System.out.println(inputLine);
        }
        in.close();
    }
}