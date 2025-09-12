import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Pinger {
    private String url;

    public Pinger(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            int exitValue = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder pong = new StringBuilder();

            while ((line = reader.readLine()) != null) {
                pong.append(line).append("\n");
            }

            if (exitValue == 0) {
                System.out.println("The URL " + url + " is alive.");
            } else {
                System.out.println("The URL " + url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            Pinger pinger = new Pinger(args[0]);
            pinger.ping();
        } else {
            System.out.println("Please provide a URL to ping.");
        }
    }
}