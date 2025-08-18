import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindToPing() throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec("ping " + url);
        StringBuilder output = new StringBuilder();
        
        try (BufferedReader reader = 
                 new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        }

        int exitCode = process.waitFor();
        String pong = output.toString();

        if (exitCode == 0) {
            System.out.println("URL " + url + " is alive.");
        } else {
            System.out.println("URL " + url + " is not alive.");
        }
        
        System.out.println(pong);
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        PingDecorator pingDecorator = new PingDecorator("google.com");
        pingDecorator.bindToPing();
    }
}