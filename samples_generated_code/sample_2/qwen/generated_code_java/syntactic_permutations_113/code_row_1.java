import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.get;

public class PingDecorator {

    public static void main(String[] args) {
        String url = "ping";
        get("/" + url, new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String pong = pingUrl(url);
                if (pong.equals("0")) {
                    return "Ping successful!";
                } else {
                    return "Ping failed with code: " + pong;
                }
            }
        });
    }

    private static String pingUrl(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                StringBuilder output = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
                return "0";
            } else {
                return String.valueOf(exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return "-1";
        }
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>PingDecorator</groupId>
    <artifactId>PingDecorator</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>