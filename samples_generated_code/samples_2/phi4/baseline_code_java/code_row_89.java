import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            boolean isAlive = exitCode == 0;
            System.out.println("Ping to " + url + ": " + (isAlive ? "alive" : "not alive"));
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java PingDecorator <url>");
            return;
        }
        String url = args[0];
        PingDecorator decorator = new PingDecorator(url);
        decorator.ping();
    }
}