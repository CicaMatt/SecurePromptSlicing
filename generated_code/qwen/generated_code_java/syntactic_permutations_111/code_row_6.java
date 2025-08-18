import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public static String ping(String url) {
        StringBuilder output = new StringBuilder();
        Process p;
        try {
            p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        } catch (IOException e) {
            return "Error: " + e.getMessage();
        }
        return output.toString();
    }

    public static void main(String[] args) {
        // Example usage
        String url = "www.google.com";
        System.out.println(ping(url));
    }
}