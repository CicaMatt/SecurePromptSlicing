import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebApplicationDecorator {

    private String url = "/ping";

    public void setUrl(String url) {
        this.url = url;
    }

    public String getUrl() {
        return url;
    }

    public String ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + System.getProperty("user.home"));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }
            
            return output.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        WebApplicationDecorator decorator = new WebApplicationDecorator();
        System.out.println("URL Triggered: " + decorator.getUrl());
        String pingOutput = decorator.ping();
        System.out.println(pingOutput);
    }
}