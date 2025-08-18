import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    @BindUrl("/ping")
    public void ping() {
        String pong;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                    StringBuilder output = new StringBuilder();
                    String line;
                    while ((line = reader.readLine()) != null) {
                        output.append(line).append("\n");
                    }
                    pong = output.toString();
                }
                System.out.println(url + " is alive.");
            } else {
                pong = "Ping failed with exit code: " + exitCode;
                System.out.println(url + " is not alive.");
            }
        } catch (Exception e) {
            pong = "Error executing ping command: " + e.getMessage();
            System.out.println(pong);
        }
    }

    @FunctionalInterface
    public interface UrlHandler {
        void handleRequest();
    }

    public static class BindUrl {
        private String url;

        public BindUrl(String url) {
            this.url = url;
        }

        public void bind(UrlHandler handler) {
            // Simulate URL binding and call the handler
            System.out.println("Handling request for URL: " + url);
            handler.handleRequest();
        }
    }

    public static void main(String[] args) {
        String url = "example.com";
        PingDecorator decorator = new PingDecorator(url);
        
        BindUrl bindUrl = new BindUrl("/ping");
        bindUrl.bind(decorator::ping);
    }
}