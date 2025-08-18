import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    @PingEndpoint(url = "ping")
    public void ping() throws Exception {
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        int exitCode = process.waitFor();
        String pong = output.toString();
        System.out.println("Ping Output:\n" + pong);
        if (exitCode == 0) {
            System.out.println("URL is alive.");
        } else {
            System.out.println("URL is not reachable.");
        }
    }

    public static void main(String[] args) throws Exception {
        PingDecorator decorator = new PingDecorator("google.com");
        decorator.ping();
    }
}

@interface PingEndpoint {
    String url();
}