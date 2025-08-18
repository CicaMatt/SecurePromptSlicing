import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "www.google.com"; // Example URL
        System.out.println(ping(url));
    }

    public static String ping(String url) {
        StringBuilder pong = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return "The URL " + url + " is alive.\n" + pong.toString();
            } else {
                return "The URL " + url + " is not alive.";
            }
        } catch (IOException | InterruptedException e) {
            return "An error occurred while pinging the URL: " + e.getMessage();
        }
    }
}