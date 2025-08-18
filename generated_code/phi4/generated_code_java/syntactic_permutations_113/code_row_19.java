import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;
    private String pong;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url); // For Unix-like systems
            // Process process = Runtime.getRuntime().exec("ping -n 4 " + url); // For Windows systems
            
            BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
            BufferedReader stdError = new BufferedReader(new InputStreamReader(process.getErrorStream()));

            StringBuilder output = new StringBuilder();
            String line;
            
            while ((line = stdInput.readLine()) != null) {
                output.append(line).append("\n");
            }

            pong = output.toString();

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("The URL " + url + " is alive.");
            } else {
                System.out.println("The URL " + url + " is not reachable.");
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
        pingDecorator.ping();
        System.out.println(pingDecorator.getPong());
    }
}