import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UrlPingDecorator {

    private String url;
    private String pong;

    public UrlPingDecorator(String url) {
        this.url = url;
    }

    public void bind() {
        if (url != null && !url.isEmpty()) {
            try {
                Process process = Runtime.getRuntime().exec("ping " + url);
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                
                StringBuilder output = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
                pong = output.toString();

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
    }

    public static void main(String[] args) {
        UrlPingDecorator decorator = new UrlPingDecorator("example.com");
        decorator.bind();

        // Output the result of the ping command
        System.out.println(decorator.pong);
    }
}