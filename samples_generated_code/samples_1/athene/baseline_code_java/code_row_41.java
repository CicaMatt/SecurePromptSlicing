import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    @BindUrl("/ping")
    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            if (exitCode == 0) {
                System.out.println("URL is alive: " + pong);
            } else {
                System.out.println("URL is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @interface BindUrl {}
}