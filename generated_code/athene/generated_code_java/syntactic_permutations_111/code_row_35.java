import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    @WebRoute("/ping")
    public String ping(String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            reader.close();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
        return output.toString();
    }

    @FunctionalInterface
    public interface WebRoute {
        String value();
    }

    // Dummy annotation to compile the code. In a real scenario, this would be provided by a web framework.
    public static class WebRouteAnnotation implements WebRoute {
        private final String url;

        public WebRouteAnnotation(String url) {
            this.url = url;
        }

        @Override
        public String value() {
            return url;
        }
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        System.out.println(service.ping("google.com"));
    }
}