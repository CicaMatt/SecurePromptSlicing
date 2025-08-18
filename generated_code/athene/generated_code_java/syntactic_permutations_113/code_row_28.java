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
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url.replace("http://", ""));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                pong = reader.lines().reduce((a, b) -> a + "\n" + b).orElse("");
                System.out.println(pong);
            } else {
                System.err.println("Ping failed with exit code " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new PingDecorator().bindFunctionToUrl();
    }
}