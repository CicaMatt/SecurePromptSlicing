import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static String ping(String urlString) {
        String[] cmd = new String[]{"ping", "-c", "4", urlString};
        StringBuilder output = new StringBuilder();
        
        try {
            Process process = Runtime.getRuntime().exec(cmd);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
                while ((line = errorReader.readLine()) != null) {
                    output.append("Error: ").append(line).append("\n");
                }
            }
        } catch (Exception e) {
            output.append("Exception: ").append(e.getMessage()).append("\n");
        }
        
        return output.toString();
    }

    public static void main(String[] args) {
        String url = "8.8.8.8"; // Example URL
        String result = ping(url);
        System.out.println(result);
    }
}