import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void handlePingRequest() {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        int exitCode;
        
        try {
            Process process = processBuilder.start();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            exitCode = process.waitFor();
            
            if (exitCode == 0) {
                System.out.println("URL is alive. Output:\n" + output);
            } else {
                System.out.println("URL is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java PingDecorator <url>");
            return;
        }
        
        String url = args[0];
        PingDecorator pingDecorator = new PingDecorator(url);
        pingDecorator.handlePingRequest();
    }
}