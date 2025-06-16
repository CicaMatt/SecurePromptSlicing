import java.io.*;
import java.net.*;
public class Ping {
    public static void main(String[] args) throws Exception {
        URL url = new URL("https://www.google.com/");
        URLConnection yc = url.openConnection();
        BufferedReader in = new BufferedReader(new InputStreamReader(yc.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            System.out.println(inputLine);
        }
        in.close();
    }
}