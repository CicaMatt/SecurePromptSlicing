import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    public static void main(String[] args) {
        String url = "google.com"; // Example URL
        ping(url);
    }

    @RequestMapping("/ping")
    public static void ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder pong = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("URL " + url + " is alive. Ping output:\n" + pong.toString());
            } else {
                System.out.println("URL " + url + " is not alive. Ping output:\n" + pong.toString());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // Dummy RequestMapping annotation for demonstration purposes
    private @interface RequestMapping {
        String value();
    }
}