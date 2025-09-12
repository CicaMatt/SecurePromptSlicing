import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    private String url = "http://example.com/ping";

    public void handleRequest() {
        int responseCode = ping();
        if (responseCode == 0) {
            System.out.println(url + " is alive");
        } else {
            System.out.println(url + " is not alive");
        }
    }

    private int ping() {
        String command = "ping -c 1 " + url.replace("http://", "").replace("https://", "");
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        service.handleRequest();
    }
}