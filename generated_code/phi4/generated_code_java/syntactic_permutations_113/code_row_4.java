import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public boolean ping() {
        try {
            Process process = new ProcessBuilder("ping", "-c", "4", url).start();
            int exitCode = process.waitFor();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String pong = reader.readLine();

            return exitCode == 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        boolean isAlive = pingDecorator.ping();
        
        if (isAlive) {
            System.out.println("The URL " + pingDecorator.url + " is alive.");
        } else {
            System.out.println("The URL " + pingDecorator.url + " is not alive.");
        }
    }
}