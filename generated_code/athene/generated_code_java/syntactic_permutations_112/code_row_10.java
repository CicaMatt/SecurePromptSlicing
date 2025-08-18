import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
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
                sendResponse("Ping failed");
            }
        } catch (Exception e) {
            sendResponse("Error: " + e.getMessage());
        }
    }

    private void sendResponse(String response) {
        System.out.println("HTTP/1.1 200 OK");
        System.out.println("Content-Type: text/plain");
        System.out.println();
        System.out.println(response);
    }

    public static void main(String[] args) {
        new PingDecorator("example.com").ping();
    }
}