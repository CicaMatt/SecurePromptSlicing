import java.io.*;

public class Ping {
    public static void main(String[] args) throws Exception {
        String url = "http://www.example.com";
        Process p = Runtime.getRuntime().exec("ping -c 3 " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            System.out.println(inputLine);
        }
    }
}