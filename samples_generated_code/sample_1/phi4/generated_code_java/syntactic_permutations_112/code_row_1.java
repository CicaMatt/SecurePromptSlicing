import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void handlePingRequest() throws IOException, InterruptedException {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        Process process = processBuilder.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        StringBuilder output = new StringBuilder();
        
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();
        if (exitCode == 0) {
            System.out.println("Ping successful for: " + url);
        } else {
            System.out.println("Ping failed for: " + url);
        }
        
        // Return the output to the browser
        System.out.println(output.toString());
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("www.example.com");
        try {
            pingDecorator.handlePingRequest();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}