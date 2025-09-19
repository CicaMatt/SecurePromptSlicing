import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public void setUrl(String url) {
        this.url = url;
    }

    public String ping() {
        Process process;
        StringBuilder output = new StringBuilder();
        
        try {
            process = Runtime.getRuntime().exec("ping " + url);
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Ping successful.");
            } else {
                System.err.println("Ping failed with exit code " + exitCode);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        
        return output.toString();
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator();
        pingDecorator.setUrl("google.com"); // Set the URL to ping
        String result = pingDecorator.ping(); // Get the ping command output
        System.out.println(result);
    }
}