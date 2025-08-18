import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void handlePingRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String s;
            while ((s = stdInput.readLine()) != null) {
                output.append(s).append("\n");
            }
            
            if (output.toString().contains("1 received")) {
                System.out.println("URL is alive: " + url);
            } else {
                System.out.println("URL is not alive: " + url);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        pingDecorator.handlePingRequest();
    }
}