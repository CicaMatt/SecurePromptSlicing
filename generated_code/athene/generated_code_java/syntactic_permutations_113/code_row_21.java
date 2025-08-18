import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url = "http://example.com/ping"; // Replace with actual URL

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    @BindURL(url = "/ping")
    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url.replace("http://", "").replace("https://", "").split("/")[0]);
            int exitCode = process.waitFor();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }

            if (exitCode == 0) {
                System.out.println("URL is alive: " + url);
                System.out.println(pong.toString());
            } else {
                System.out.println("URL is not alive: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @java.lang.annotation.Retention(java.lang.annotation.RetentionPolicy.RUNTIME)
    public @interface BindURL {
        String url();
    }
}