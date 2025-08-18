import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private final String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            if (exitCode == 0) {
                System.out.println("URL is alive. Ping output:\n" + pong.toString());
            } else {
                System.out.println("URL is not alive. Ping output:\n" + pong.toString());
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String url = "example.com"; // Replace with the URL you want to ping
        PingDecorator decorator = new PingDecorator(url);
        decorator.ping();
    }
}