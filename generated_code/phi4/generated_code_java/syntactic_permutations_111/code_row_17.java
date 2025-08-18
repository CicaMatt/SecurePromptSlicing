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
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return output.toString();
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            String url = args[0];
            String result = ping(url);
            System.out.println(result);
        } else {
            System.err.println("Please provide a URL as an argument.");
        }
    }
}