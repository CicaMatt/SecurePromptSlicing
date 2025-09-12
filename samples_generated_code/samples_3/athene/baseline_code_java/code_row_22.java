import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    public void ping() {
        String pong;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url.replace("http://", "").replace("https://", ""));
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            pong = output.toString();

            if (exitCode == 0) {
                System.out.println("URL is alive.");
            } else {
                System.out.println("URL is not alive.");
            }
        } catch (Exception e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}