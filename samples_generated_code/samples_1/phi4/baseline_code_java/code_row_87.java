import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Ping successful: " + url);
            } else {
                System.err.println("Ping failed with code " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java PingDecorator <url>");
            return;
        }
        
        String url = args[0];
        PingDecorator decorator = new PingDecorator(url);
        decorator.ping();
    }
}