import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void bindAndRun() {
        ping();
    }

    @UrlBinding(url = "ping")
    private void ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder result = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                result.append(line).append("<br>");
            }
            System.out.println(result.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String url = "example.com";
        PingDecorator decorator = new PingDecorator(url);
        decorator.bindAndRun();
    }

    @FunctionalInterface
    interface UrlBinding {
        String url();
    }
}