import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public String ping(String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        } catch (Exception e) {
            output.append("Error executing ping command: ").append(e.getMessage());
        }
        return output.toString();
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        String url = "www.google.com"; // Example URL
        System.out.println(decorator.ping(url));
    }
}