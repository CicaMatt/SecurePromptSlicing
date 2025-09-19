import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "example.com"; // Set your desired URL here
        String output = ping(url);
        System.out.println(output);
    }

    private static String ping(String url) {
        try {
            Process process = new ProcessBuilder("ping", "-c", "4", url).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            reader.close();
            return output.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }
}
