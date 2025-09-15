import java.io.BufferedReader;
import java.io.InputStreamReader;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class PingDecorator {

    public static void main(String[] args) {
        Spark.get("/ping", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String url = request.queryParams("url");
                if (url == null || url.isEmpty()) {
                    return "URL parameter is required.";
                }
                String pong = pingUrl(url);
                if (pong != null && !pong.isEmpty()) {
                    return pong;
                } else {
                    return "Ping failed or URL is unreachable.";
                }
            }
        });
    }

    private static String pingUrl(String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
                return output.toString();
            } else {
                return "Ping command failed with exit code: " + exitCode;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}
