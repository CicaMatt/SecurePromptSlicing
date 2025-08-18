import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    @Bind(url = "/ping")
    public String ping() {
        String pong = "";
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            if (exitCode == 0) {
                pong = "is alive";
                reader.lines().forEach(System.out::println); // Optionally print the ping output
            } else {
                pong = "is not alive";
            }
        } catch (Exception e) {
            e.printStackTrace();
            pong = "is not alive";
        }
        return url + " " + pong;
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("google.com");
        System.out.println(decorator.ping());
    }

    @interface Bind {
        String url();
    }
}