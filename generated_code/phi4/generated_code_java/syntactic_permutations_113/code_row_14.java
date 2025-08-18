import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public boolean checkUrlAlive() {
        Process process;
        try {
            process = Runtime.getRuntime().exec("ping -c 1 " + this.url);
            int exitCode = process.waitFor();
            return exitCode == 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        
        if (pingDecorator.checkUrlAlive()) {
            System.out.println("URL is alive.");
        } else {
            System.out.println("URL is not alive.");
        }
    }
}