import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        // Example usage
        String url = "8.8.8.8";  // Replace with desired URL or IP address
        String output = ping(url);
        System.out.println(output);
    }

    public static String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url); // '-c 4' for Unix-like systems, change to '-n 4' for Windows
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error executing ping command.";
        }
    }
}