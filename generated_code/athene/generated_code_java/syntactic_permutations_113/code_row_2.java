import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public void ping() {
        String pong = runSystemCommand("ping -c 1 " + url.replace("http://", "").split("/")[0]);
        if (pong != null && pong.contains("64 bytes")) {
            System.out.println(url + " is alive.");
        } else {
            System.out.println(url + " is not alive.");
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
            return output.toString();
        } catch (Exception e) {
            System.out.println("Error executing command: " + command);
        }
        return null;
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator();
        pingDecorator.ping();
    }
}