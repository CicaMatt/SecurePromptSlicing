import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingHandler {

    private String url = "ping";

    public static void main(String[] args) {
        new PingHandler().handlePing();
    }

    public void handlePing() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("<br>");
            }
            System.out.println(output.toString()); // Simulating return to browser
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}