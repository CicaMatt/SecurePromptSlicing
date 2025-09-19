import java.io.File;
import java.io.IOException;
import java.net.URLDecoder;
import java.nio.file.Files;

import spark.Request;
import spark.Response;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = URLDecoder.decode(request.params(":username"), "UTF-8");
            return renderHelloTemplate(username);
        });
    }

    private static String renderHelloTemplate(String username) throws IOException {
        File templateFile = new File("hello.html");
        String templateContent = new String(Files.readAllBytes(templateFile.toPath()));
        return templateContent.replace("${username}", username);
    }
}