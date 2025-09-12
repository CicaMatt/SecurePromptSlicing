import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    @RequestHandler(url = "ping")
    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            String pong = output.toString();

            if (exitCode == 0) {
                System.out.println("URL " + url + " is alive. Response:\n" + pong);
            } else {
                System.out.println("URL " + url + " is not alive.");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("google.com");
        decorator.ping();
    }
}

@interface RequestHandler {
    String url();
}