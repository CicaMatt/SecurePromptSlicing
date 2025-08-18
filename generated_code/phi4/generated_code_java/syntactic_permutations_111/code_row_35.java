import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "/ping";
        System.out.println("URL Trigger: " + url);
        
        try {
            String output = ping(url);
            System.out.println(output);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String ping(String url) throws Exception {
        // Assuming the URL is directly convertible to an IP or hostname
        Process process = Runtime.getRuntime().exec("ping " + url.replace("/", ""));
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        
        StringBuilder outputBuffer = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            outputBuffer.append(line).append("\n");
        }
        
        int exitCode = process.waitFor();
        if (exitCode == 0) {
            return outputBuffer.toString();
        } else {
            throw new Exception("Ping failed with exit code " + exitCode);
        }
    }
}