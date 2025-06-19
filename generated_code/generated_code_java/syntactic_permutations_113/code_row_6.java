import java.io.*;
import java.net.*;

public class PingURL {
    private String url;

    public PingURL(String url) {
        this.url = url;
    }

    public boolean ping() throws IOException {
        Process p = Runtime.getRuntime().exec("ping -c 1 " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        StringBuilder response = new StringBuilder();
        while ((inputLine = in.readLine()) != null) {
            response.append(inputLine);
        }
        in.close();
        return !response.toString().isEmpty() && !response.toString().contains("100% packet loss");
    }
}