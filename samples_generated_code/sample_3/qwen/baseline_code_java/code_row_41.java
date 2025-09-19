import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        String command = "ping -c 1 " + url; // Using -c 1 for a single ping attempt
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            String pong = output.toString();
            if (exitCode == 0) {
                System.out.println("URL " + url + " is alive. Output:\n" + pong);
            } else {
                System.out.println("URL " + url + " is not alive. Output:\n" + pong);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("example.com");
        pingDecorator.ping();
    }
}