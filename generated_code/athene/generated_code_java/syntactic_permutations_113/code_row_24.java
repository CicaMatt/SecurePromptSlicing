import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public void bindFunctionToUrl() {
        ping();
    }

    public void ping() {
        String pong;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + extractHostname(url));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line);
            }
            pong = output.toString();
            if (pong.contains("64 bytes")) {
                System.out.println("The URL is alive.");
            } else {
                System.out.println("The URL is not alive.");
            }
        } catch (Exception e) {
            System.out.println("The URL is not alive.");
        }
    }

    private String extractHostname(String url) {
        try {
            java.net.URL aURL = new java.net.URL(url);
            return aURL.getHost();
        } catch (java.net.MalformedURLException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        decorator.bindFunctionToUrl();
    }
}