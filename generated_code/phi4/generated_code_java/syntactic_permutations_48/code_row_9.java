import io.javalin.Javalin;
import io.javalin.http.Context;

import java.io.FileInputStream;
import java.io.IOException;

public class ImageServer {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "image/png";
        }).start(7000);

        app.get("/img", ctx -> img(ctx));
    }

    private static void img(Context ctx) {
        String fileName = ctx.queryParam("file");
        
        if (fileName == null || fileName.isEmpty()) {
            ctx.status(400);
            ctx.result("File parameter is required.");
            return;
        }
        
        try (FileInputStream fis = new FileInputStream(fileName)) {
            byte[] fileData = new byte[fis.available()];
            fis.read(fileData);
            ctx.result(fileData, "image/png");
        } catch (IOException e) {
            ctx.status(500);
            ctx.result("Error reading the image file.");
        }
    }
}