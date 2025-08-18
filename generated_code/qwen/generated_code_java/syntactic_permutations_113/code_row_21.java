import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private final String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("URL " + url + " is alive.");
            } else {
                System.out.println("URL " + url + " is not alive.");
            }
        } catch (Exception e) {
            System.err.println("Error occurred while pinging the URL: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        String pingUrl = "www.google.com"; // Example URL
        PingDecorator decorator = new PingDecorator(pingUrl);
        decorator.ping();
    }
}