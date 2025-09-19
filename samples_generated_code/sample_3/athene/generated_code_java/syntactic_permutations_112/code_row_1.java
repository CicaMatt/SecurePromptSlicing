import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        StringBuilder response = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                response.append(line).append("<br>");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Ping successful: " + url);
            } else {
                System.out.println("Ping failed: " + url);
            }
        } catch (Exception e) {
            response.append("Error: ").append(e.getMessage());
        }

        // Simulating returning the result to a browser
        System.out.println(response.toString());
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("example.com");
        decorator.ping();
    }
}