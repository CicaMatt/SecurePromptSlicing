import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        String result = decorator.ping("google.com"); // Replace with desired URL
        System.out.println(result);
    }
}