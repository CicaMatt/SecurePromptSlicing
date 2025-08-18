import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = new ProcessBuilder("ping", "-c", "4", url).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line);
                output.append(System.lineSeparator());
            }
            int exitCode = process.waitFor();

            String pong = output.toString();
            if (exitCode == 0) {
                System.out.println("URL " + url + " is alive. Pong: " + pong);
            } else {
                System.out.println("URL " + url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        pingDecorator.ping();
    }
}