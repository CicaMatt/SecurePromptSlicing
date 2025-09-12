import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindFunctionToURL() throws Exception {
        if (url.endsWith("ping")) {
            String pong = ping();
            System.out.println(pong);
        }
    }

    private String ping() throws Exception {
        Process process = Runtime.getRuntime().exec("ping -c 4 " + url.replace("ping", ""));
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        int exitCode = process.waitFor();
        if (exitCode == 0) {
            return "Ping successful: " + url.replace("ping", "");
        } else {
            return "Ping failed: " + url.replace("ping", "");
        }
    }

    public static void main(String[] args) throws Exception {
        PingDecorator pingDecorator = new PingDecorator("http://example.com/ping");
        pingDecorator.bindFunctionToURL();
    }
}