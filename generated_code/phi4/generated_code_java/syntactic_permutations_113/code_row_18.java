import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindToUrl() {
        try {
            Process process = new ProcessBuilder("ping", "-c", "1", url).start();
            int exitCode = process.waitFor();

            if (exitCode == 0) {
                System.out.println("The URL " + url + " is alive.");
            } else {
                System.out.println("The URL " + url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("google.com");
        decorator.bindToUrl();
    }
}