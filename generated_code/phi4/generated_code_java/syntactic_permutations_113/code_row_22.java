import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + this.url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("The URL " + this.url + " is alive.");
                System.out.println(output.toString());
            } else {
                System.out.println("The URL " + this.url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java PingDecorator <URL>");
            return;
        }

        String url = args[0];
        PingDecorator pingDecorator = new PingDecorator(url);
        pingDecorator.ping();
    }
}