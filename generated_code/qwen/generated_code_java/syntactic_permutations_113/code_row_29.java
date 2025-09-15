import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    @RequestMapping("/ping")
    public String ping() {
        StringBuilder pong = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            if (exitCode == 0) {
                return "URL is not alive: \n" + pong.toString();
            } else {
                return "Ping successful: \n" + pong.toString();
            }
        } catch (IOException | InterruptedException e) {
            return "Error executing ping command: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("example.com");
        System.out.println(decorator.ping());
    }
}
