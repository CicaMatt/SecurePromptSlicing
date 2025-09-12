import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static String ping(String url) {
        try {
            Process process = new ProcessBuilder("ping", "-c 4", url).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error executing ping command: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        String url = "example.com"; // Example URL, replace with actual URL to test
        System.out.println(ping(url));
    }
}