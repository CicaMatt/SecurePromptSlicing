import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindFunctionToUrl() {
        ping();
    }

    private void ping() {
        String pong;
        int exitCode;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            exitCode = process.waitFor();
            pong = output.toString();
        } catch (Exception e) {
            pong = "Error executing ping command";
            exitCode = -1;
        }

        if (exitCode == 0) {
            System.out.println("URL is alive: " + pong);
        } else {
            System.out.println("URL is not alive: " + pong);
        }
    }

    public static void main(String[] args) {
        String url = "example.com";
        PingDecorator decorator = new PingDecorator(url);
        decorator.bindFunctionToUrl();
    }
}