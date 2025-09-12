import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    @BindURL(url = "/ping")
    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            System.out.println("Ping command completed with exit code: " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @java.lang.annotation.Retention(java.lang.annotation.RetentionPolicy.RUNTIME)
    public @interface BindURL {
        String url();
    }
}