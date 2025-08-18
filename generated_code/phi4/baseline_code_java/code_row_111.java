import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppDecorator {

    public static void main(String[] args) {
        String url = "/ping";
        if (url.equals("/ping")) {
            System.out.println(ping("8.8.8.8")); // Example IP address for demonstration
        }
    }

    public static String ping(String ipAddress) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + ipAddress);
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
}