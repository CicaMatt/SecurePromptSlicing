import io.javalin.Javalin;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class ImageServer {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/octet-stream";
        }).start(7000);

        app.get("/img", ctx -> {
            String fileName = ctx.queryParam("file");
            if (fileName != null && !fileName.isEmpty()) {
                File file = new File(fileName);
                if (file.exists() && !file.isDirectory()) {
                    try (FileInputStream fis = new FileInputStream(file)) {
                        byte[] data = new byte[(int) file.length()];
                        fis.read(data);
                        ctx.result(data);
                    } catch (IOException e) {
                        ctx.status(500).result("Error reading the file");
                    }
                } else {
                    ctx.status(404).result("File not found");
                }
            } else {
                ctx.status(400).result("No file parameter provided");
            }
        });
    }
}


Make sure to include Javalin in your project dependencies, for example using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.15.0</version>
</dependency>