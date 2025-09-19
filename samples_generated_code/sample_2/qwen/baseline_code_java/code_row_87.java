import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URLConnection;
import java.util.stream.Collectors;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class PingDecorator {

    public static void main(String[] args) {
        Spark.get("/ping", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String url = "www.example.com"; // URL to ping
                return ping(url);
            }
        });
    }

    private static String ping(String url) {
        StringBuilder result = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url); // For Windows use "ping -n 4 " + url
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            result.append(reader.lines().collect(Collectors.joining("\n")));
        } catch (IOException e) {
            return "Error: " + e.getMessage();
        }
        return result.toString();
    }
}