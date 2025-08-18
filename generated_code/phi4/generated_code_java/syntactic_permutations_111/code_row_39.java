import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class WebApplication {

    public static void main(String[] args) {
        String url = "www.example.com";
        String result = ping(url);
        System.out.println(result);
    }

    public static String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            return output.toString();

        } catch (IOException e) {
            e.printStackTrace();
            return "Error: Unable to execute ping command.";
        }
    }
}