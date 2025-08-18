import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "example.com"; // Example URL, replace with actual URL as needed
        PingDecorator decorator = new PingDecorator();
        System.out.println(decorator.ping(url));
    }

    public String ping(String url) {
        StringBuilder output = new StringBuilder();
        Process process;
        try {
            process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        } catch (IOException e) {
            return "Error: " + e.getMessage();
        }
        return output.toString();
    }
}