import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class WebAppPingDecorator {

    public static void main(String[] args) {
        String url = "http://example.com"; // Set your URL here
        System.out.println(ping(url));
    }

    private static String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (IOException e) {
            e.printStackTrace();
            return "Ping failed: " + e.getMessage();
        }
    }
}