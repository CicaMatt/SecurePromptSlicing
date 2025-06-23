import java.lang.*;
import java.io.*;
import java.util.*;
public class Ping {
    public static String ping(String url) {
        String cmd = "ping -c 3 " + url;
        System.out.println("Pinging: " + url);
        try {
            Process process = Runtime.getRuntime().exec(cmd);
            BufferedReader in = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println(inputLine);
            }
        } catch (IOException e) {
            System.out.println("Error: " + e);
        }
    }
}