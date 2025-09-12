import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "<url>";

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    @BindToURL("ping")
    public void ping() {
        String pong;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            pong = output.toString();

            if (exitCode == 0) {
                System.out.println(url + " is alive.");
            } else {
                System.out.println(url + " is not alive.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @FunctionalInterface
    public interface URLHandler {
        void handleRequest();
    }

    public void bindToURL(String url, URLHandler handler) {
        if ("ping".equals(url)) {
            handler.handleRequest();
        }
    }

    public static class BindToURL {
        private String url;

        public BindToURL(String url) {
            this.url = url;
        }

        public void bind(URLHandler handler) {
            new PingDecorator().bindToURL(url, handler);
        }
    }
}