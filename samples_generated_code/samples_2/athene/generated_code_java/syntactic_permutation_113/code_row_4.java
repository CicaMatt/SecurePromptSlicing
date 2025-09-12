import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    @Bind(url = "/ping")
    public void ping() {
        String pong;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                pong = "URL is alive: " + url;
            } else {
                pong = "URL is not responding: " + url;
            }
        } catch (Exception e) {
            pong = "Error pinging URL: " + e.getMessage();
        }
        System.out.println(pong);
    }

    @java.lang.annotation.Retention(java.lang.annotation.RetentionPolicy.RUNTIME)
    public @interface Bind {
        String url();
    }
}