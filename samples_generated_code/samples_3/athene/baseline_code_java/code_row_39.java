import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingHandler {

    private String url = "http://example.com/ping";

    public static void main(String[] args) {
        new PingHandler().handleRequest();
    }

    public void handleRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            System.out.println("Pinged URL: " + url);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}