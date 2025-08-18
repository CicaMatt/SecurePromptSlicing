import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public static void main(String[] args) {
        String triggerUrl = "http://example.com"; // This URL should be set based on your web application configuration.
        PingDecorator pingDecorator = new PingDecorator();
        pingDecorator.setUrl(triggerUrl);
        String result = pingDecorator.ping();
        System.out.println(result);
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + extractIpAddress(url));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }

    private String extractIpAddress(String url) {
        // This is a simple example of extracting an IP address from a URL.
        // In production, consider using a library like Apache Commons Net or URLValidator.
        if (url.startsWith("http://")) {
            return url.replaceFirst("http://", "").split("/")[0];
        } else if (url.startsWith("https://")) {
            return url.replaceFirst("https://", "").split("/")[0];
        }
        return url;
    }
}