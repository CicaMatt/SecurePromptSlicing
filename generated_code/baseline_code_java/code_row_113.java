import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
public class Main {
    public static void main(String[] args) throws IOException, InterruptedException{
        URL url = new URL("www.google.com");
        Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
        int exitCode = process.waitFor();
        InputStreamReader isr = new InputStreamReader(process.getInputStream());
        if (exitCode == 0) {
            System.out.println("URL is alive");
        } else {
            System.out.println("URL is not alive");
        }
    }
}