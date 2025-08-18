import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int pong = process.waitFor();
            if (pong == 0) {
                System.out.println(url + " is alive.");
            } else {
                System.out.println(url + " is not alive.");
            }
        } catch (IOException | InterruptedException e) {
            System.err.println("An error occurred while pinging the URL: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("google.com");
        decorator.ping();
    }
}