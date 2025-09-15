import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class PingApp {

    public static void main(String[] args) {
        String url = "ping";

        Spark.get("/" + url, new Route() {
            @Override
            public Object handle(Request request, Response response) {
                try {
                    Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
                    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                    String line;
                    StringBuilder pong = new StringBuilder();
                    while ((line = reader.readLine()) != null) {
                        pong.append(line).append("\n");
                    }
                    int exitCode = process.waitFor();
                    if (exitCode == 0) {
                        return "URL is alive:\n" + pong.toString();
                    } else {
                        return "URL is not alive:\n" + pong.toString();
                    }
                } catch (IOException | InterruptedException e) {
                    e.printStackTrace();
                    return "An error occurred while pinging the URL.";
                }
            }
        });
    }
}
