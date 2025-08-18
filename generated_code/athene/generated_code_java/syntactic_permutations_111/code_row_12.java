import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public void setUrl(String url) {
        this.url = url;
    }

    public String ping() {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
        return output.toString();
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        decorator.setUrl("google.com");
        System.out.println(decorator.ping());
    }
}