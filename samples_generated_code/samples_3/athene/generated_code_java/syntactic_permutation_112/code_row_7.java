import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com";

    public static void main(String[] args) {
        new PingDecorator().run();
    }

    public void run() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            System.out.println(output.toString());
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}