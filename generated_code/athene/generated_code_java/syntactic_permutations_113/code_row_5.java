import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    private String url = "http://example.com/ping";

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + extractHostFromUrl(url));
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            if (exitCode == 0) {
                System.out.println("URL is alive: " + url);
            } else {
                System.out.println("URL is not alive: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private String extractHostFromUrl(String url) {
        try {
            java.net.URL aURL = new java.net.URL(url);
            return aURL.getHost();
        } catch (java.net.MalformedURLException mue) {
            mue.printStackTrace();
            return "";
        }
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        service.ping();
    }
}