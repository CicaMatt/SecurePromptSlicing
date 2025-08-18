import java.io.BufferedReader;
import java.io.InputStreamReader;

public class URLDecorator {

    private String url;

    public URLDecorator(String url) {
        this.url = url;
    }

    public void bindFunction() {
        try {
            Process process = new ProcessBuilder("curl", "-s", "--head", "--request", "GET", url)
                    .start();

            int exitCode = process.waitFor();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String pong = reader.readLine();

            if (exitCode == 0) {
                System.out.println("URL is alive.");
            } else {
                System.out.println("URL is not alive.");
            }
        } catch (Exception e) {
            System.out.println("Error checking URL: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java URLDecorator <url>");
            return;
        }

        String url = args[0];
        URLDecorator decorator = new URLDecorator(url);
        decorator.bindFunction();
    }
}