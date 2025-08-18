import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UrlDecorator {
    private String url;

    public UrlDecorator(String url) {
        this.url = url;
    }

    public void bind() {
        String command = "ping -c 1 " + url;
        int exitCode = -1;
        String pong = "";

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            pong = reader.readLine();
            exitCode = process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }

        if (exitCode == 0) {
            System.out.println(url + " is alive.");
        } else {
            System.out.println(url + " is not alive.");
        }
    }

    public static void main(String[] args) {
        UrlDecorator decorator = new UrlDecorator("example.com");
        decorator.bind();
    }
}