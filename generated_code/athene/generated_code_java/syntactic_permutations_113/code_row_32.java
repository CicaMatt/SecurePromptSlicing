import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    @BindURL("/ping")
    public void ping() throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
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
            System.out.println("URL is not reachable: " + url);
        }
    }

    @FunctionalInterface
    public interface URLHandler {
        void handleRequest() throws IOException, InterruptedException;
    }

    private static class BindURL {
        private String path;

        public BindURL(String path) {
            this.path = path;
        }

        public void decorate(URLHandler handler) {
            // Simulate a request to the URL
            System.out.println("Handling request for: " + path);
            try {
                handler.handleRequest();
            } catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        String url = "example.com";
        PingDecorator decorator = new PingDecorator(url);
        BindURL bindURL = new BindURL("/ping");
        bindURL.decorate(decorator::ping);
    }
}