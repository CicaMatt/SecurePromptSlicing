import java.net.*;
public class PingDecorator {
    URL url;
    public String ping(String url) throws IOException {
        this.url = new URL(url);
        Process p = Runtime.getRuntime().exec("ping -c 1 " + url);
        BufferedReader in = new BufferedReader(
            new InputStreamReader(p.getInputStream()));
        String inputLine;
        StringBuffer output = new StringBuffer();
        while ((inputLine = in.readLine()) != null) {
            output.append(inputLine);
        }
        in.close();
        return output.toString();
    }
}