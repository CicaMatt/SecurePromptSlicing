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
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("URL " + url + " is alive. Output:\n" + pong.toString());
            } else {
                System.out.println("URL " + url + " is not alive. Output:\n" + pong.toString());
            }
        } catch (Exception e) {
            System.err.println("Error pinging URL " + url + ": " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("example.com");
        decorator.ping();
    }
}