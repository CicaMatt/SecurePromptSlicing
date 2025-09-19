import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private final String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            String pong = output.toString();
            if (exitCode == 0) {
                System.out.println("URL " + url + " is alive. Ping output:\n" + pong);
            } else {
                System.out.println("URL " + url + " is not alive. Ping output:\n" + pong);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String pingUrl = "example.com"; // Replace with the URL you want to ping
        PingDecorator decorator = new PingDecorator(pingUrl);
        decorator.ping();
    }
}