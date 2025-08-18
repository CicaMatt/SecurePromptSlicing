import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static String ping(String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = 
                new BufferedReader(new InputStreamReader(process.getInputStream()));
                
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            reader.close();
            process.waitFor();

        } catch (Exception e) {
            e.printStackTrace();
        }

        return output.toString();
    }

    public static void main(String[] args) {
        String url = "8.8.8.8"; // Example URL
        System.out.println(ping(url));
    }
}