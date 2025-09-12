import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static String ping(String url) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
            Process process = processBuilder.start();
            
            StringBuilder output = new StringBuilder();
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

        } catch (Exception e) {
            return "Error occurred: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        String url = "example.com";  // Replace with the desired URL
        String result = ping(url);
        System.out.println(result);
    }
}