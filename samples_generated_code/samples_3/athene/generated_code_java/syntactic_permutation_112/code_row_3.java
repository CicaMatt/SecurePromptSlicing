import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com";

    public void bind() {
        System.out.println("Bound URL: " + url);
    }

    public String ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url.replace("http://", ""));
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
        decorator.bind();
        String result = decorator.ping();
        System.out.println(result);
    }
}