import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingHandler {

    private String url;

    public PingHandler(String url) {
        this.url = url;
    }

    @Decorator(url = "http://example.com/ping")
    public String handlePing() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }

    @FunctionalInterface
    public interface Decorator {
        String url();
    }
}