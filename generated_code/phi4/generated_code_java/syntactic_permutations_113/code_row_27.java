import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;
    private String pong;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void handlePingRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            pong = output.toString();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Ping successful for URL: " + url);
            } else {
                System.err.println("Ping failed for URL: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com"); // Replace with desired URL
        pingDecorator.handlePingRequest();
    }
}