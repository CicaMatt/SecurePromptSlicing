import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public String ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            if (exitCode == 0) {
                return "URL is alive: " + url + "\nPong:\n" + output.toString();
            } else {
                return "URL is not alive: " + url;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "Error pinging the URL: " + url;
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java PingDecorator <url>");
            return;
        }
        
        String url = args[0];
        PingDecorator decorator = new PingDecorator(url);
        String result = decorator.ping();
        System.out.println(result);
    }
}