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


Make sure to add the Spark dependency in your project. If you are using Maven, add this to your `pom.xml`:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


If you are using Gradle, add this to your `build.gradle`:


dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
}