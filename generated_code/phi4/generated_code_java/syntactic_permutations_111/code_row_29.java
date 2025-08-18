import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws IOException, InterruptedException {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        processBuilder.redirectErrorStream(true);

        Process process = processBuilder.start();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new IOException("Ping command failed with exit code " + exitCode);
        }
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a URL as an argument.");
            return;
        }

        String url = args[0];
        PingDecorator pingDecorator = new PingDecorator(url);

        try {
            pingDecorator.ping();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}