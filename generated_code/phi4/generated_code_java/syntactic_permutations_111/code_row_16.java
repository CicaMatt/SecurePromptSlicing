import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebPingDecorator {

    public static String ping(String url) {
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
            e.printStackTrace();
            return "Error executing ping command: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        String url = "example.com"; // Replace with the desired URL
        String result = ping(url);
        System.out.println("Ping Result for " + url + ":\n" + result);
    }
}