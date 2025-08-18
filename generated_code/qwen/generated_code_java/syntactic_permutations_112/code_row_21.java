import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws IOException {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", url);
        Process process = processBuilder.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }

        int exitCode = process.waitFor();
        System.out.println("Exited with error code: " + exitCode);
    }

    public static void main(String[] args) {
        try {
            PingDecorator pingDecorator = new PingDecorator("google.com");
            pingDecorator.ping();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}