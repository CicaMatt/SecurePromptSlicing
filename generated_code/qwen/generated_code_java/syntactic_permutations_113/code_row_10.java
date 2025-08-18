import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

class PingDecorator {
    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            if (exitCode == 0) {
                System.out.println("URL is alive. Response:\n" + pong.toString());
            } else {
                System.out.println("URL is not alive.");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        String url = "google.com"; // Example URL
        PingDecorator decorator = new PingDecorator(url);
        decorator.ping();
    }
}