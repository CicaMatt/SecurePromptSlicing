import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    @Bind(url = "/ping")
    public void ping() throws Exception {
        String pong;
        int exitCode;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            exitCode = process.waitFor();
            pong = output.toString();
        } catch (Exception e) {
            throw new Exception("Error executing ping command", e);
        }

        if (exitCode == 0) {
            System.out.println(url + " is alive.\nPong: " + pong);
        } else {
            System.out.println(url + " is not alive.");
        }
    }

    @FunctionalInterface
    public interface Bindable {
        void execute() throws Exception;
    }

    public static class Bind {
        private String url;

        public Bind(String url) {
            this.url = url;
        }

        public void bind(Bindable bindable) throws Exception {
            if (this.url.equals("/ping")) {
                bindable.execute();
            }
        }
    }

    @java.lang.annotationRetention(java.lang.annotation.RetentionPolicy.RUNTIME)
    @java.lang.annotation.Target({java.lang.annotation.ElementType.METHOD})
    public @interface Bind {
        String url();
    }

    public static void main(String[] args) throws Exception {
        PingDecorator decorator = new PingDecorator("example.com");
        Bind bindAnnotation = new Bind("/ping");
        bindAnnotation.bind(decorator::ping);
    }
}