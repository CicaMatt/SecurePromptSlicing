import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url = "<url>";

    @Bind(url = "/ping")
    public void ping() {
        String pong;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                    StringBuilder output = new StringBuilder();
                    String line;
                    while ((line = reader.readLine()) != null) {
                        output.append(line).append("\n");
                    }
                    pong = output.toString();
                }
                System.out.println(url + " is alive.");
            } else {
                pong = "Failed to ping " + url;
                System.out.println(url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @FunctionalInterface
    public interface Bind {
        String url();
    }
}