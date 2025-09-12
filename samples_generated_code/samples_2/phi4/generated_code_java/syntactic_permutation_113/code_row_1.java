import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    private String url = "example.com";

    public void handlePingRequest() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitValue = process.waitFor();
            
            if (exitValue == 0) {
                System.out.println(url + " is alive.");
            } else {
                System.out.println(url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingService pingService = new PingService();
        pingService.handlePingRequest();
    }
}