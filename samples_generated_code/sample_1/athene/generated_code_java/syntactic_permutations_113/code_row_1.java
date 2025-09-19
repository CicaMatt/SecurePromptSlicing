import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    private String url = "<url>";

    public void bindFunctionToUrl(String url, Runnable function) {
        this.url = url;
        function.run();
    }

    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        decorator.bindFunctionToUrl("ping", decorator::ping);
    }

    private void ping() {
        String pong = executePingCommand(url);
        if (pong != null) {
            System.out.println(pong);
        } else {
            System.out.println("Ping command failed.");
        }
    }

    private String executePingCommand(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
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
}