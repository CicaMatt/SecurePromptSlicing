import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static String ping(String urlString) {
        String url = urlString;
        StringBuilder output = new StringBuilder();
        
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return output.toString();
    }

    public static void main(String[] args) {
        // Example usage
        String result = ping("8.8.8.8"); // Replace with any URL/IP you want to test
        System.out.println(result);
    }
}