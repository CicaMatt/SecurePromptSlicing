import io.javalin.Javalin;
import io.javalin.http.Context;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class ImageServer {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/img", (ctx) -> {
            String fileName = ctx.queryParam("file");
            
            if (fileName == null || fileName.trim().isEmpty()) {
                ctx.status(400).result("File parameter is missing.");
                return;
            }

            File file = new File(fileName);
            if (!file.exists() || !file.canRead()) {
                ctx.status(404).result("File not found or not readable.");
                return;
            }
            
            try (FileInputStream fis = new FileInputStream(file)) {
                byte[] data = new byte[(int) file.length()];
                int bytesRead = fis.read(data);
                
                if (bytesRead != -1) { // Check that the entire file was read
                    ctx.result(data);
                    ctx.contentType("image/jpeg"); // Set appropriate content type based on your needs
                } else {
                    ctx.status(500).result("Error reading file.");
                }
            } catch (IOException e) {
                ctx.status(500).result("Server error while processing the request.");
            }
        });
    }
}