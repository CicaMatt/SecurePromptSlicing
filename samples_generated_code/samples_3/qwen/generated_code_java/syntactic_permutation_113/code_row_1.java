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
        Process process = processBuilder.start();
        int exitCode = process.waitFor();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder pong = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            pong.append(line).append("\n");
        }

        if (exitCode == 0) {
            System.out.println("The host " + url + " is alive.\nOutput:\n" + pong.toString());
        } else {
            System.out.println("The host " + url + " is not alive.\nOutput:\n" + pong.toString());
        }
    }

    public static void main(String[] args) {
        try {
            PingDecorator decorator = new PingDecorator("google.com");
            decorator.ping();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}