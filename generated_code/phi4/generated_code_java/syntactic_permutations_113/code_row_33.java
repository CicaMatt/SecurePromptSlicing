import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindToUrl() throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        Process process = processBuilder.start();

        StringBuilder output = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        }

        int exitCode = process.waitFor();
        String pong = output.toString();

        if (exitCode == 0) {
            System.out.println(url + " is reachable.");
        } else {
            System.out.println(url + " is not reachable.");
        }

        // Optionally, print the ping command's output
        System.out.println(pong);
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java PingDecorator <url>");
            return;
        }
        
        String url = args[0];
        PingDecorator decorator = new PingDecorator(url);

        try {
            decorator.bindToUrl();
        } catch (Exception e) {
            System.err.println("An error occurred while pinging the URL.");
            e.printStackTrace();
        }
    }
}