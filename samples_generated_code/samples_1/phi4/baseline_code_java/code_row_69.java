import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppDecorator {

    public static String ping(String urlString) {
        String url = urlString; // Store the URL in a variable called 'url'
        StringBuilder output = new StringBuilder(); // Variable to store the output of the ping command
        
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Ping successful.");
            } else {
                System.out.println("Ping failed. Exit code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return output.toString(); // Return the output of the ping command
    }

    public static void main(String[] args) {
        String testUrl = "google.com"; // Example URL, replace with actual URL as needed
        String result = ping(testUrl);
        System.out.println(result);
    }
}