import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import spark.Request;
import spark.Response;
import spark.Spark;

public class PingApp {
    public static void main(String[] args) {
        String url = "ping";

        Spark.get("/" + url, (Request request, Response response) -> {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        });
    }
}