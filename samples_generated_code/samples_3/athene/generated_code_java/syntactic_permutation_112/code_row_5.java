import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com"; // Example URL

    public static void main(String[] args) {
        new PingDecorator().handleRequest();
    }

    public void handleRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            System.out.println(output.toString());
        } catch (Exception e) {
            System.out.println("Error pinging " + url);
            e.printStackTrace();
        }
    }
}