import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public void ping() {
        String pong = executePingCommand();
        if (pong != null && pong.contains("0")) {
            System.out.println(url + " is alive");
        } else {
            System.out.println(url + " is not alive");
        }
    }

    private String executePingCommand() {
        StringBuilder output = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = p.waitFor();
            return exitCode == 0 ? "0" : "1";
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator("google.com");
        decorator.ping();
    }
}