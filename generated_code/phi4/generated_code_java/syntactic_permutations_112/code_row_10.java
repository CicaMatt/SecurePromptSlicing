import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UrlDecoratorExample {

    private String url;

    public UrlDecoratorExample(String url) {
        this.url = url;
    }

    public void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Ping successful for URL: " + url);
            } else {
                System.out.println("Ping failed for URL: " + url);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String url = "google.com"; // Example URL
        UrlDecoratorExample example = new UrlDecoratorExample(url);
        example.ping();
    }
}