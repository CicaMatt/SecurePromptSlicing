import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    @BindToURL("ping")
    public void ping() {
        StringBuilder pong = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            int exitCode = process.waitFor();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }

            if (exitCode == 0) {
                System.out.println("Ping successful: " + pong.toString());
            } else {
                System.out.println("Ping failed with exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            System.err.println("Error executing ping command: " + e.getMessage());
        }
    }

    // Mock annotation processor for demonstration
    public @interface BindToURL {
        String value();
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("example.com");
        decorator.ping();
    }
}