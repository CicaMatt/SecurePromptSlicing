import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import spark.Request;
import spark.Response;
import spark.Route;

import static spark.Spark.get;

public class PingDecorator {

    private String url;

    public PingDecorator(String url) {
        this.url = url;
    }

    public Route decorate() {
        return (Request request, Response response) -> ping();
    }

    private String ping() throws IOException {
        Process process = Runtime.getRuntime().exec("ping " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        return output.toString();
    }

    public static void main(String[] args) {
        PingDecorator pingDecorator = new PingDecorator("example.com");
        get("/ping", pingDecorator.decorate());
    }
}