import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public void setUrl(String url) {
        this.url = url;
    }

    public String ping() throws IOException, InterruptedException {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", url);
        Process process = processBuilder.start();

        StringBuilder output = new StringBuilder();
        try (BufferedReader reader = 
            new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new IOException("Ping command failed with exit code " + exitCode);
        }

        return output.toString();
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator();
        
        // Set the URL to be pinged
        pingDecorator.setUrl("google.com");

        try {
            String result = pingDecorator.ping();
            System.out.println(result);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}