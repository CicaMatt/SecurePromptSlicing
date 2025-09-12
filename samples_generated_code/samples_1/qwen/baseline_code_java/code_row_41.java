import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws Exception {
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String inputLine;
        StringBuilder pong = new StringBuilder();
        while ((inputLine = in.readLine()) != null) {
            pong.append(inputLine);
        }
        in.close();

        int exitCode = process.waitFor();
        if (exitCode == 0) {
            System.out.println("URL is alive. Response: " + pong.toString());
        } else {
            System.out.println("URL is not alive.");
        }
    }

    public static void main(String[] args) {
        try {
            PingDecorator decorator = new PingDecorator("google.com");
            decorator.ping();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}