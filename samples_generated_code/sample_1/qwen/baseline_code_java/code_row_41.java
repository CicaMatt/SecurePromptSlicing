import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec("ping " + url);
        int exitCode = process.waitFor();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;

        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        String pong = output.toString();

        if (exitCode == 0) {
            System.out.println("URL is alive: " + url);
        } else {
            System.out.println("URL is not alive: " + url);
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        PingDecorator pingDecorator = new PingDecorator("example.com");
        pingDecorator.ping();
    }
}