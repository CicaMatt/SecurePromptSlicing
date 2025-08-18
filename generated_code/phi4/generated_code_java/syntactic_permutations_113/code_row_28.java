import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void handlePingRequest() {
        String pong = runPingCommand();
        if (pong.contains("0 received")) {
            System.out.println(url + " is reachable.");
        } else {
            System.out.println(url + " is not reachable.");
        }
    }

    private String runPingCommand() {
        Process process;
        StringBuilder output = new StringBuilder();

        try {
            process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            return output.toString() + "\nExit Code: " + exitCode;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return "Error executing ping command";
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java PingDecorator <url>");
            return;
        }

        String url = args[0];
        PingDecorator decorator = new PingDecorator(url);
        decorator.handlePingRequest();
    }
}