import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "<url>";

    public static void main(String[] args) {
        new PingDecorator().ping();
    }

    @BindURL(url = "ping")
    public void ping() {
        String pong;
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + this.url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            pong = output.toString();
            if (exitCode == 0) {
                System.out.println(this.url + " is reachable.");
            } else {
                System.out.println(this.url + " is not reachable.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @java.lang.annotation.Retention(java.lang.annotation.RetentionPolicy.RUNTIME)
    public @interface BindURL {
        String url();
    }
}