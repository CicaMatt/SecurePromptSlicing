import java.io.IOException;
import java.lang.ProcessBuilder;
public class Ping {
    public static void main(String[] args) throws IOException, InterruptedException {
        String url = "www.google.com";
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c 1 ", url);
        Process p = processBuilder.start();
        int pingStatus = p.waitFor();
        if (pingStatus == 0) {
            System.out.println("URL is alive");
        } else {
            System.out.println("URL is not alive");
        }
    }
}