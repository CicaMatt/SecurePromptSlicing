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
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                StringBuilder output = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
                pong = output.toString();
                System.out.println(url + " is alive.");
            } else {
                System.out.println(url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String url = "example.com"; // URL to ping
        PingDecorator decorator = new PingDecorator(url);
        decorator.ping();
    }
}