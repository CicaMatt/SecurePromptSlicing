import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public String ping() throws IOException, InterruptedException {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", url);
        Process process = processBuilder.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;

        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();
        if (exitCode == 0) {
            return "Ping successful:\n" + output.toString();
        } else {
            return "Ping failed with exit code: " + exitCode;
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        try {
            String result = pingDecorator.ping();
            System.out.println(result);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}