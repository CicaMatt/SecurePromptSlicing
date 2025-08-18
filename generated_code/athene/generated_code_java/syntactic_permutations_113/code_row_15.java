import java.io.BufferedReader;
import java.io.InputStreamReader;

public class URLDecorator {
    private String url;

    public URLDecorator(String url) {
        this.url = url;
    }

    public void bindFunctionToURL() throws Exception {
        String command = "ping -c 1 " + url;
        Process process = Runtime.getRuntime().exec(command);
        int exitCode = process.waitFor();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder pong = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            pong.append(line);
        }
        if (exitCode == 0) {
            System.out.println(url + " is alive. Output: " + pong.toString());
        } else {
            System.out.println(url + " is not alive.");
        }
    }

    public static void main(String[] args) throws Exception {
        URLDecorator decorator = new URLDecorator("example.com");
        decorator.bindFunctionToURL();
    }
}