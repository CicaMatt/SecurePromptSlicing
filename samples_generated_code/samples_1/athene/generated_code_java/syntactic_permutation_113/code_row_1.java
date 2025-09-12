import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public void bindFunctionToUrl() {
        ping();
    }

    private void ping() {
        String pong = "";
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url.replace("http://", "").replace("https://", ""));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line);
            }
            pong = output.toString();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println(url + " responded with: " + pong);
            } else {
                System.out.println(url + " did not respond.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new PingDecorator().bindFunctionToUrl();
    }
}