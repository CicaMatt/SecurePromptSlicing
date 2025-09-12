import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void handlePingRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + this.url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        pingDecorator.handlePingRequest();
    }
}