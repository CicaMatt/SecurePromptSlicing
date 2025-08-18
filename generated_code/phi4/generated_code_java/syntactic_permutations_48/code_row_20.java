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
                        byte[] fileContent = new byte[(int) file.length()];
                        int bytesRead = fis.read(fileContent);
                        if (bytesRead != -1) {
                            ctx.result(fileContent, 200);
                        } else {
                            ctx.status(404).result("File not found");
                        }
                    } catch (IOException e) {
                        ctx.status(500).result("Server error: " + e.getMessage());
                    }
                } else {
                    ctx.status(404).result("File not found");
                }
            } else {
                ctx.status(400).result("Bad request, 'file' parameter is required");
            }
        });
    }
}