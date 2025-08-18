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
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String pong = reader.readLine();

            if (exitCode == 0) {
                System.out.println(url + " is not alive.");
            } else {
                System.out.println(pong != null ? pong : "");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            String url = args[0];
            PingDecorator decorator = new PingDecorator(url);
            decorator.handlePingRequest();
        } else {
            System.out.println("Please provide a URL as an argument.");
        }
    }
}