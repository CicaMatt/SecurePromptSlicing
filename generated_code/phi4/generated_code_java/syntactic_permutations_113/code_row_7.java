import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws IOException, InterruptedException {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "1", url);
        Process process = processBuilder.start();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String pong = reader.readLine();
            if (pong != null && pong.contains("bytes from")) {
                System.out.println(url + " is alive.");
            } else {
                System.out.println(url + " is not alive.");
            }
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new RuntimeException(url + " ping failed with exit code: " + exitCode);
        }
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a URL to ping.");
            return;
        }
        
        String url = args[0];
        PingDecorator decorator = new PingDecorator(url);

        try {
            decorator.ping();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}