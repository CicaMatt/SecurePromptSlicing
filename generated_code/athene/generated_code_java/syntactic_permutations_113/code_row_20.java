import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public void bind(String url, Runnable function) {
        this.url = url;
        function.run();
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        decorator.bind("http://example.com/ping", decorator::ping);
    }

    public void ping() {
        String pong = executePingCommand(url);
        if (pong != null && pong.contains("time=")) {
            System.out.println(url + " is alive.");
        } else {
            System.out.println(url + " is not alive.");
        }
    }

    private String executePingCommand(String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec("ping -c 1 " + url.replace("http://", "").replace("https://", ""));
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitVal = p.waitFor();
            if (exitVal == 0) {
                return output.toString();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}