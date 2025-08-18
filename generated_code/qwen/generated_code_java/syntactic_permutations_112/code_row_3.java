import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class PingApp {
    public static void main(String[] args) {
        Spark.get("/ping", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String url = "google.com"; // Example URL to ping
                return ping(url);
            }
        });
    }

    private static String ping(String url) {
        StringBuilder result = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                result.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return result.toString();
            } else {
                return "Ping failed with exit code: " + exitCode;
            }
        } catch (IOException | InterruptedException e) {
            return "Error executing ping command: " + e.getMessage();
        }
    }
}