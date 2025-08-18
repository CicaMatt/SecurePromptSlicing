import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void pingUrl() throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c 4", url);
        Process process = processBuilder.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }

        int exitCode = process.waitFor();
        if (exitCode == 0) {
            System.out.println("Ping to " + url + " was successful.");
        } else {
            System.err.println("Ping to " + url + " failed with error code: " + exitCode);
        }
    }

    public static void main(String[] args) throws Exception {
        String urlToPing = "example.com"; // Replace with the desired URL
        PingDecorator pingDecorator = new PingDecorator(urlToPing);
        pingDecorator.pingUrl();
    }
}