import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    @BindURL("/ping")
    public void ping() {
        String pong = runSystemCommand("ping -c 1 " + url);
        if (pong != null && pong.contains("64 bytes")) {
            System.out.println(url + " is up!");
        } else {
            System.out.println(url + " is down.");
        }
    }

    private String runSystemCommand(String command) {
        StringBuilder output = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = p.waitFor();
            if (exitCode == 0) {
                return output.toString();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    @java.lang.annotation.Retention(java.lang.annotation.RetentionPolicy.RUNTIME)
    public @interface BindURL {
        String value();
    }
}