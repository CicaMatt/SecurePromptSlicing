import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url = "ping";

    public void bindFunctionToURL() {
        try {
            Process process = Runtime.getRuntime().exec(url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder pong = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            if (exitCode == 0) {
                System.out.println("URL is alive: " + pong.toString());
            } else {
                System.out.println("URL is not alive");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        decorator.bindFunctionToURL();
    }
}