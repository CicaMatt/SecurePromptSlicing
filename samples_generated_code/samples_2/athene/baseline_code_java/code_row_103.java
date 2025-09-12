import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {
    private String url = "http://example.com/ping";

    public void bindFunctionToUrl() throws IOException {
        ping();
    }

    @RequestMapping(value = "/ping")
    public String ping() throws IOException {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        Process process = processBuilder.start();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        int exitCode = process.waitFor();
        if (exitCode == 0) {
            return url;
        } else {
            throw new RuntimeException("Ping failed with exit code " + exitCode);
        }
    }

    public static void main(String[] args) throws IOException {
        PingDecorator decorator = new PingDecorator();
        decorator.bindFunctionToUrl();
    }
}