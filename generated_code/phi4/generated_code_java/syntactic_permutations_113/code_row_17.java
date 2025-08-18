import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindToUrl(String baseUrl) {
        System.out.println("Binding function to URL: " + baseUrl + "ping");
        try {
            Process process = new ProcessBuilder("ping", "-c", "4", url).start();
            StringBuilder pong = new StringBuilder();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("URL is alive: " + url);
                System.out.println(pong.toString());
            } else {
                System.out.println("URL is not alive: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("example.com");
        pingDecorator.bindToUrl("/ping"); // Example URL base
    }
}