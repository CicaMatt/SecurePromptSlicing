import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindToUrl() throws Exception {
        Process process = new ProcessBuilder("ping", "-c", "4", url).start();
        StringBuilder output = new StringBuilder();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        }

        int exitCode = process.waitFor();
        if (exitCode == 0) {
            System.out.println("URL is alive.");
        } else {
            System.out.println("URL is not alive.");
        }
    }

    public static void main(String[] args) throws Exception {
        PingDecorator pingDecorator = new PingDecorator("example.com");
        pingDecorator.bindToUrl();
    }
}