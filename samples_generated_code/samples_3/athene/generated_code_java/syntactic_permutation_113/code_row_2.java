import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com"; // Replace with actual URL

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url.replace("http://", "").replace("https://", ""));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            int exitCode = process.waitFor();

            if (exitCode == 0) {
                System.out.println(url + " is alive.");
            } else {
                System.out.println(url + " is not alive.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}