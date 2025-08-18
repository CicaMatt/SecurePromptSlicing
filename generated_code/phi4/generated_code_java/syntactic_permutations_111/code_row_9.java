import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebApplicationDecorator {

    private String url;

    public void setUrl(String url) {
        this.url = url;
    }

    public String getUrl() {
        return url;
    }

    public String ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
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

    public static void main(String[] args) {
        WebApplicationDecorator app = new WebApplicationDecorator();
        app.setUrl("example.com"); // Replace with desired URL
        System.out.println(app.ping());
    }
}