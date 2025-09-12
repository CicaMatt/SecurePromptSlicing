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
            pong = output.toString();
            if (exitCode == 0) {
                System.out.println("URL is alive: " + url);
            } else {
                System.out.println("URL is not alive: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @interface Bind {
        String url();
    }
}