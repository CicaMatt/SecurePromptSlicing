import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingDecorator().bind("/ping", PingDecorator::ping);
    }

    public void bind(String path, Runnable handler) {
        if (path.equals("/ping")) {
            handler.run();
        }
    }

    public static void ping() {
        String url = new PingDecorator().url;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Pong: " + pong.toString());
            } else {
                System.out.println("Failed to ping: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}