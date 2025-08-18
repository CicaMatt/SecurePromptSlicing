import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url = "http://example.com/ping";

    public void ping() {
        String pong;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url.replace("http://", "").replace("/", ""));
            int exitCode = process.waitFor();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                StringBuilder output = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
                pong = output.toString();
            }
            if (exitCode == 0) {
                System.out.println(url + " is alive.");
            } else {
                System.out.println(url + " is not alive.");
            }
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        decorator.ping();
    }
}