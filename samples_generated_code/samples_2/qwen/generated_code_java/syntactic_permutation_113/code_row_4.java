import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            int exitCode = process.waitFor();
            StringBuilder output = new StringBuilder();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            String pong = output.toString();
            if (exitCode == 0) {
                System.out.println("URL is alive. Output:\n" + pong);
            } else {
                System.out.println("URL is not reachable. Output:\n" + pong);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("example.com");
        decorator.ping();
    }
}