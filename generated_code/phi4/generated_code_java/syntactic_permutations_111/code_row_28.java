import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebPingDecorator {

    public static String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return "Ping successful:\n" + output.toString();
            } else {
                return "Ping failed with exit code: " + exitCode;
            }

        } catch (Exception e) {
            return "Error during ping execution: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        String url = "www.example.com"; // Replace with the URL you want to test
        System.out.println(ping(url));
    }
}