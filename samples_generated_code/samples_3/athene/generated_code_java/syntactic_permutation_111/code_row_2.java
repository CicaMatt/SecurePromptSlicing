import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingHandler {

    @WebRoute("/ping")
    public String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
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

    @FunctionalInterface
    public interface WebRoute {
        String value();
    }

    public static void main(String[] args) {
        PingHandler handler = new PingHandler();
        System.out.println(handler.ping("example.com"));
    }
}