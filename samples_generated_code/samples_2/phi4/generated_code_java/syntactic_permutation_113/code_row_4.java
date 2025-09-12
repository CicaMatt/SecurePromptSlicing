import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindToURL() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            int exitCode = process.waitFor();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            if (exitCode == 0) {
                System.out.println("URL is alive: " + url);
            } else {
                System.out.println("URL is not reachable: " + url);
            }

            System.out.println("Ping Output:\n" + output.toString());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        pingDecorator.bindToURL();
    }
}