import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingDecorator().handleRequest();
    }

    public void handleRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url.replace("http://", "").replace("/", ""));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println(url);
            } else {
                System.out.println("Ping failed");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}