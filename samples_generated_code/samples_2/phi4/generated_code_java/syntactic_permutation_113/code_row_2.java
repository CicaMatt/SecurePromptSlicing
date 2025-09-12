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
        StringBuilder output = new StringBuilder();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        }

        int exitCode = process.waitFor();

        if (exitCode == 0) {
            System.out.println("The URL " + url + " is alive.");
        } else {
            System.out.println("The URL " + url + " is not alive.");
        }

        System.out.println("Ping output: \n" + output);
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java PingDecorator <url>");
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