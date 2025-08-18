import java.io.IOException;
import java.util.concurrent.Callable;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public Callable<String> decorate(Callable<String> task) {
        return () -> {
            int pingResult = runPingCommand(url);
            if (pingResult == 0) {
                return "URL is alive";
            } else {
                return "URL is not alive";
            }
        };
    }

    private int runPingCommand(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            Thread.currentThread().interrupt();
            return -1;
        }
    }

    public static void main(String[] args) {
        String url = "example.com";
        PingDecorator decorator = new PingDecorator(url);
        Callable<String> pingTask = decorator.decorate(() -> "Ping result");

        try {
            System.out.println(pingTask.call());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}