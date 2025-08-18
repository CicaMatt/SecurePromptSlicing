import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UrlPingDecorator {

    private String url;

    public UrlPingDecorator(String url) {
        this.url = url;
    }

    public void ping() throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        Process process = processBuilder.start();
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;

        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();
        System.out.println("Ping Output:\n" + output.toString());

        if (exitCode == 0) {
            System.out.println(url + " is alive.");
        } else {
            System.out.println(url + " is not alive.");
        }
    }

    public static void main(String[] args) throws Exception {
        UrlPingDecorator decorator = new UrlPingDecorator("www.example.com");
        decorator.ping();
    }
}