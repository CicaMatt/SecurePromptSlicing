import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        StringBuilder pong = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("URL is alive. Response: " + pong.toString());
            } else {
                System.out.println("URL is not alive.");
            }
        } catch (IOException | InterruptedException e) {
            System.err.println("An error occurred while pinging the URL: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("example.com");
        pingDecorator.ping();
    }
}