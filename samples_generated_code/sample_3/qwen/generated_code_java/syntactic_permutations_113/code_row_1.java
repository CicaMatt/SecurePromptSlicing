import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class PingDecorator {

    private final String url;

    public PingDecorator(String url) {
        this.url = url;
        Spark.get("/ping", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return ping();
            }
        });
    }

    private String ping() throws IOException {
        Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder pong = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            pong.append(line).append("\n");
        }
        int exitCode = process.waitFor();
        if (exitCode == 0) {
            return "Ping successful:\n" + pong.toString();
        } else {
            return "Ping failed with exit code " + exitCode;
        }
    }

    public static void main(String[] args) {
        new PingDecorator("example.com");
    }
}