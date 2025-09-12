import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "/ping";
        System.out.println("URL Triggered: " + url);
        
        String result = ping(url);
        System.out.println("Ping Output: \n" + result);
    }

    public static String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 google.com");
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