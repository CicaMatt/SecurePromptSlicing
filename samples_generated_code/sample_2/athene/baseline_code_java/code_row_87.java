import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingHandler {

    private String url = "http://example.com";

    public static void main(String[] args) {
        new PingHandler().handlePing();
    }

    public void handlePing() {
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
            System.out.println("Error pinging " + url);
            e.printStackTrace();
        }
    }
}