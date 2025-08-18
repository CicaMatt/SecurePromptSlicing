import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindAndRun() throws Exception {
        ping();
    }

    public String ping() throws Exception {
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("<br>");
        }
        return output.toString(); // This would be sent to the browser in a web application context
    }

    public static void main(String[] args) throws Exception {
        PingDecorator decorator = new PingDecorator("example.com");
        String result = decorator.ping();
        System.out.println(result); // For demonstration purposes, print to console
    }
}