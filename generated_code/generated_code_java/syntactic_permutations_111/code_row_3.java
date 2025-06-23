import java.io.*;
import java.net.*;
public class ping {
    public static void main(String[] args) throws IOException {
        URL url = new URL(args[0]);
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            System.out.println(inputLine);
        }
        in.close();
    }
}