import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingHandler {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingHandler().handleRequest();
    }

    public void handleRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            System.out.println(output.toString());
            System.out.println("Pinged URL: " + url);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}