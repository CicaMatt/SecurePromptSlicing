import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bind() {
        new Thread(() -> pingUrl(url)).start();
    }

    private void pingUrl(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                sendResponse(url);
            } else {
                sendResponse("Failed to ping " + url);
            }
        } catch (Exception e) {
            sendResponse("Error: " + e.getMessage());
        }
    }

    private void sendResponse(String response) {
        // Simulate sending a response to the browser
        System.out.println("Browser Response: " + response);
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("google.com");
        decorator.bind();
    }
}