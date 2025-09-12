import java.io.BufferedReader;
import java.io.InputStreamReader;
import spark.Spark;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "/ping";
        Spark.get(url, (req, res) -> {
            Process process = Runtime.getRuntime().exec("ping " + req.queryParams("address"));
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return "Pong: \n" + output.toString();
            } else {
                return "Ping failed with exit code: " + exitCode;
            }
        });
    }
}