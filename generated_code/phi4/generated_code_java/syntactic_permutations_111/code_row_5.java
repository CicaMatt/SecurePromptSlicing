import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public String ping() throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        
        process.waitFor();
        return output.toString();
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a URL as an argument.");
            return;
        }
        
        String url = args[0];
        PingDecorator pingDecorator = new PingDecorator(url);
        
        try {
            String result = pingDecorator.ping();
            System.out.println(result);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}