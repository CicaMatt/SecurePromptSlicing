import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "<url> ping";

    public static void main(String[] args) {
        new PingDecorator().runPing();
    }

    private void runPing() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + getUrlToPing());
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("URL is not alive.");
            } else {
                System.out.println(pong);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private String getUrlToPing() {
        return url.split(" ")[0];
    }
}