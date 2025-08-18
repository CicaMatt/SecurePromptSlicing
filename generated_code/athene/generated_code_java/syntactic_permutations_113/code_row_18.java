import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindFunctionToUrl(Runnable function) {
        function.run();
    }

    public void ping() {
        String command = "ping -c 1 " + url; // Adjust the ping command based on OS
        int exitCode = -1;

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            exitCode = process.waitFor();

            if (exitCode == 0) {
                System.out.println(url + " is alive.");
            } else {
                System.out.println(url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String url = "example.com";
        PingDecorator decorator = new PingDecorator(url);
        decorator.bindFunctionToUrl(decorator::ping);
    }
}