import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "http://example.com/ping";

    public void bindFunctionToUrl() {
        ping();
    }

    private void ping() {
        String pong = executePingCommand(url);
        if (pong != null) {
            System.out.println(pong);
        } else {
            System.out.println("Ping failed");
        }
    }

    private String executePingCommand(String url) {
        try {
            String[] cmd = {"ping", "-c", "1", url};
            Process process = Runtime.getRuntime().exec(cmd);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                StringBuilder output = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
                return output.toString();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void main(String[] args) {
        new PingDecorator().bindFunctionToUrl();
    }
}