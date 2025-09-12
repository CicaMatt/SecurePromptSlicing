import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindToUrl(String urlPath) {
        if ("/ping".equals(urlPath)) {
            ping();
        }
    }

    private void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            int exitCode = process.waitFor();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();
            
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            String pong = output.toString();
            if (exitCode == 0) {
                System.out.println("URL is alive: " + url);
            } else {
                System.out.println("URL is not alive: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("example.com");
        decorator.bindToUrl("/ping");
    }
}