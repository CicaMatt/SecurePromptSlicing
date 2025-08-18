import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebAppDecorator {
    private String url;

    public WebAppDecorator(String url) {
        this.url = url;
    }

    public String ping() throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        Process process = processBuilder.start();
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        
        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new Exception("Ping failed with exit code " + exitCode);
        }
        
        return output.toString();
    }

    public static void main(String[] args) {
        try {
            WebAppDecorator decorator = new WebAppDecorator("www.example.com");
            String result = decorator.ping();
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}