import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingHandler {

    private String url = "http://example.com";

    public static void main(String[] args) {
        new PingHandler().handleRequest();
    }

    @Bind(url = "/ping")
    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            System.out.println(output.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void handleRequest() {
        ping(); // Simulating a request to /ping
    }

    @interface Bind {
        String url();
    }
}