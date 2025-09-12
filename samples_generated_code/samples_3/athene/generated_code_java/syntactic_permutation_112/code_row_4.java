import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com";

    public static void main(String[] args) {
        new PingDecorator().handleRequest("/ping");
    }

    public void handleRequest(String requestUrl) {
        if (requestUrl.equals("/ping")) {
            ping();
        }
    }

    private void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                output.append(line).append("<br>");
            }
            System.out.println(output.toString()); // This would be sent to the browser in a real scenario
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}