import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import spark.Spark;

public class PingServer {
    public static void main(String[] args) {
        String url = "google.com"; // Example URL to ping

        Spark.get("/ping", (req, res) -> {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            StringBuilder pong = new StringBuilder();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    pong.append(line).append("\n");
                }
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return "URL is alive:\n" + pong.toString();
            } else {
                return "URL is not alive:\n" + pong.toString();
            }
        });
    }
}