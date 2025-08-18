import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "google.com"; // Example URL
        String result = ping(url);
        System.out.println(result); // Output to console, simulating browser return
    }

    public static String ping(String host) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + host);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return output.toString();
            } else {
                return "Ping failed with exit code: " + exitCode;
            }
        } catch (IOException | InterruptedException e) {
            return "Error executing ping command: " + e.getMessage();
        }
    }
}