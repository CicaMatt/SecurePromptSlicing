import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "google.com"; // Example URL
        String output = ping(url);
        System.out.println(output);
    }

    public static String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url); // Ping for 4 times on Unix-based systems, use "-n" for Windows
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder outputBuilder = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                outputBuilder.append(line).append("\n");
            }
            return outputBuilder.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }
}
