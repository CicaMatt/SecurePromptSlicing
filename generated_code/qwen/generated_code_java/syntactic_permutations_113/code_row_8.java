import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "example.com"; // Example URL to ping
        boolean isAlive = pingUrl(url);
        System.out.println("Is the URL " + url + " alive? " + isAlive);
    }

    public static boolean pingUrl(String url) {
        StringBuilder pong = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url); // Use "-c 4" for Unix-like systems
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line);
            }
            int exitCode = process.waitFor();
            return exitCode == 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}