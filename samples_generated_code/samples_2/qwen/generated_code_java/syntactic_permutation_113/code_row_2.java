import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private final String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
        int exitCode = process.waitFor();
        StringBuilder output = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        }
        String pong = output.toString();
        if (exitCode == 0) {
            System.out.println("URL " + url + " is alive. Output:\n" + pong);
        } else {
            System.out.println("URL " + url + " is not alive. Output:\n" + pong);
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