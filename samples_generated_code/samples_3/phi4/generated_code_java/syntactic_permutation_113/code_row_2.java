import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public boolean checkUrl() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitValue = process.waitFor();
            return exitValue == 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        boolean isAlive = pingDecorator.checkUrl();

        if (isAlive) {
            System.out.println("The URL " + pingDecorator.url + " is alive.");
        } else {
            System.out.println("The URL " + pingDecorator.url + " is not alive.");
        }
    }
}