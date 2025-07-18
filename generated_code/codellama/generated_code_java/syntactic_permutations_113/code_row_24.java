import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
public class PingDecorator {
    private String url;
    public PingDecorator(String url) {
        this.url = url;
    }
    
    public String ping() throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", url);
        Process process = processBuilder.start();
        StringBuilder output = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line + "\n");
        }
        int exitVal = process.waitFor();
        if (exitVal == 0) {
            return "Alive";
        } else {
            return "Not Alive";
        }
    }
}