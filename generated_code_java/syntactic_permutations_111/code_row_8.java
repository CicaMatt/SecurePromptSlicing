import java.io.*;

public class Ping{
    public static void main(String[] args) throws IOException {
        String url = "http://www.google.com";
        Process p = Runtime.getRuntime().exec("ping -c 1 www.google.com");
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            System.out.println(inputLine);
        }
    }
}