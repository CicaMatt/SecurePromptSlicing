import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder pong = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }

            if (exitCode == 0) {
                System.out.println("URL " + url + " is alive. Pong:\n" + pong.toString());
            } else {
                System.out.println("URL " + url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("<url>");
        decorator.ping();
    }
}