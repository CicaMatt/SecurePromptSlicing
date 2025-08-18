import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void handlePingRequest() {
        String pong = executePingCommand(url);
        if (pong.contains("0% packet loss")) {
            System.out.println(url + " is alive.");
        } else {
            System.out.println(url + " is not alive.");
        }
    }

    private String executePingCommand(String url) {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        StringBuilder output = new StringBuilder();
        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            return output.toString() + "\nExit Code: " + exitCode;

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return "Error executing ping command.";
        }
    }

    public static void main(String[] args) {
        String urlToPing = "google.com"; // Replace with desired URL
        PingDecorator pingDecorator = new PingDecorator(urlToPing);
        pingDecorator.handlePingRequest();
    }
}