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
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitValue = process.waitFor();
            String pong = output.toString();

            if (exitValue == 0) {
                System.out.println("URL is alive. Ping result:\n" + pong);
            } else {
                System.out.println("URL is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            String url = args[0];
            PingDecorator decorator = new PingDecorator(url);
            decorator.bindToURL();
        } else {
            System.out.println("Please provide a URL as an argument.");
        }
    }
}