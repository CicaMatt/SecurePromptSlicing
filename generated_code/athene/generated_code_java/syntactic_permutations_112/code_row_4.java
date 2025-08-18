import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    @Bind(url = "/ping")
    public String ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + this.url.replace("http://", "").split("/")[0]);
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
        PingDecorator decorator = new PingDecorator();
        System.out.println(decorator.ping());
    }

    @interface Bind {
        String url();
    }
}