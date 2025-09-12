import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com"; // Replace with actual URL

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    @UrlBinder(url = "http://example.com/ping")
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
                System.out.println(url + " is alive.");
            } else {
                System.out.println(url + " is not alive.");
            }
            System.out.println("Ping Output:\n" + pong.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Retention(RetentionPolicy.RUNTIME)
    @Target(ElementType.METHOD)
    public @interface UrlBinder {
        String url();
    }
}