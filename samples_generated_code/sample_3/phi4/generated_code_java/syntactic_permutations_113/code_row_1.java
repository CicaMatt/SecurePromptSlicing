import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;
    private String pong;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void handlePingRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            pong = output.toString();

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Ping to " + url + " was successful.");
            } else {
                System.out.println("Ping to " + url + " failed.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public String getPong() {
        return pong;
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        pingDecorator.handlePingRequest();

        System.out.println("Ping Output: ");
        System.out.println(pingDecorator.getPong());
    }
}