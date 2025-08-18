import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UrlPingDecorator {

    private String url = "ping";

    public void ping() {
        String pong;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            pong = output.toString();
            if (exitCode == 0) {
                System.out.println("URL is alive: " + url);
            } else {
                System.out.println("URL is not alive: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UrlPingDecorator decorator = new UrlPingDecorator();
        decorator.ping();
    }
}