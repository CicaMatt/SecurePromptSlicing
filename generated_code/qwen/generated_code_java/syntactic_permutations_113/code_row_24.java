import java.io.BufferedReader;
import java.io.InputStreamReader;
import spark.Request;
import spark.Response;
import spark.Route;

import static spark.Spark.get;

public class PingService {

    public static void main(String[] args) {
        String url = "google.com"; // Example URL, can be changed or passed as a parameter

        get("/ping", (request, response) -> ping(url));
    }

    private static String ping(String url) throws Exception {
        Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder pong = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            pong.append(line).append("\n");
        }
        int exitCode = process.waitFor();
        return exitCode == 0 ? "URL is alive: \n" + pong.toString() : "URL is not alive";
    }
}