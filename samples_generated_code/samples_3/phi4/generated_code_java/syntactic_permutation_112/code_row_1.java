import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws Exception {
        Process process = Runtime.getRuntime().exec("ping " + url);
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        
        int exitCode = process.waitFor();
        if (exitCode == 0) {
            System.out.println(url + " is reachable.");
        } else {
            System.out.println(url + " is not reachable.");
        }
    }

    public static void main(String[] args) {
        try {
            String url = "google.com";
            PingDecorator pingDecorator = new PingDecorator(url);
            pingDecorator.ping();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}