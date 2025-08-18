import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingUrl {

    private String url;

    public PingUrl(String url) {
        this.url = url;
    }

    public boolean ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitValue = process.waitFor();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            System.out.println("Ping Output: " + output.toString());
            return exitValue == 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        PingUrl pingUrl = new PingUrl("google.com");
        boolean isAlive = pingUrl.ping();

        if (isAlive) {
            System.out.println("The URL is alive.");
        } else {
            System.out.println("The URL is not alive.");
        }
    }
}