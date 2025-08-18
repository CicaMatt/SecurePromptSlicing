import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import spark.Request;
import spark.Response;
import spark.Spark;

public class PingDecoratorExample {

    private static final String url = "ping";

    public static void main(String[] args) {
        Spark.get(url, (Request req, Response res) -> ping());
    }

    private static String ping() throws IOException {
        Process process = Runtime.getRuntime().exec("ping -c 4 google.com");
        StringBuilder output = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        return output.toString();
    }
}