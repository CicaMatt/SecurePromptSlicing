import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindToUrl() {
        String pong = ping(url);
        if (pong != null && pong.contains("0% packet loss")) {
            System.out.println("URL is alive: " + url);
        } else {
            System.out.println("URL is not alive: " + url);
        }
    }

    private String ping(String target) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + target);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (Exception e) {
            System.err.println("An error occurred: " + e.getMessage());
            return null;
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        pingDecorator.bindToUrl();
    }
}