import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "example.com";
        PingDecorator decorator = new PingDecorator();
        decorator.pingUrl(url);
    }

    public void pingUrl(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url); // For Linux/Mac
            // Process process = Runtime.getRuntime().exec("ping -n 4 " + url); // For Windows
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder pong = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("URL " + url + " is alive.");
                System.out.println(pong.toString());
            } else {
                System.out.println("URL " + url + " is not alive.");
                System.out.println(pong.toString());
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}