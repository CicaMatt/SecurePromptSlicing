import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws IOException {
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        try {
            int exitCode = process.waitFor();
            System.out.println("Exited with error code: " + exitCode);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        try {
            pingDecorator.ping();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}