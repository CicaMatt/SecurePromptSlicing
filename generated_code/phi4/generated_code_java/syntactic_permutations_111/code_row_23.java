import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppPingDecorator {
    
    public static String ping(String url) throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        Process process = processBuilder.start();
        
        StringBuilder output = new StringBuilder();
        try (BufferedReader reader = 
                new BufferedReader(new InputStreamReader(process.getInputStream()))) {

            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }
        }

        return output.toString();
    }

    public static void main(String[] args) {
        try {
            String url = "www.google.com"; // Example URL, replace with actual URL if needed.
            System.out.println(ping(url));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}