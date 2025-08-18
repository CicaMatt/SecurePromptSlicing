import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public void bindUrlToFunction(String url) {
        this.url = url;
        ping();
    }

    private void ping() {
        int exitCode = -1;
        String pong = "";
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                pong += line + "\n";
            }
            exitCode = process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }

        if (exitCode == 0) {
            System.out.println("URL is alive: " + url);
        } else {
            System.out.println("URL is not alive: " + url);
        }
        System.out.println("Output:\n" + pong);
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        decorator.bindUrlToFunction("http://example.com/ping");
    }
}