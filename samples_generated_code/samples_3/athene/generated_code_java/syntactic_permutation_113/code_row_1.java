import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        int exitCode = -1;
        String pong = "";
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
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
            System.out.println("is alive");
        } else {
            System.out.println("is not alive");
        }

        System.out.println("Ping output:\n" + pong);
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("google.com");
        decorator.ping();
    }
}