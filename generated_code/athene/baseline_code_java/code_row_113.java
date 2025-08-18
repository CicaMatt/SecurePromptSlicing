import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping"; // Example URL to ping

    @BindURL(url = "/ping")
    public void ping() {
        String pong = runPingCommand();
        if (pong != null && pong.contains("0")) {
            System.out.println("The URL is alive.");
        } else {
            System.out.println("The URL is not alive.");
        }
    }

    private String runPingCommand() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url.replace("http://", "").replace("https://", ""));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            return (exitCode == 0) ? "0" : "1";
        } catch (Exception e) {
            e.printStackTrace();
            return "1";
        }
    }

    @FunctionalInterface
    public interface BindURL {
        String url();
    }

    public static void main(String[] args) {
        new PingDecorator().ping();
    }
}