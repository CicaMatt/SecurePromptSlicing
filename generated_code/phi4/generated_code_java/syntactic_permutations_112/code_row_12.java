import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Ping to " + url + " successful.");
            } else {
                System.out.println("Ping to " + url + " failed.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String url = "google.com"; // Replace with desired URL
        PingDecorator pingDecorator = new PingDecorator(url);
        pingDecorator.ping();
    }
}