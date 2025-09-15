import io.javalin.Javalin;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class ImageServer {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "image/*";
        }).start(7000);

        app.get("/img", ctx -> {
            String fileName = ctx.queryParam("file");
            File file = new File(fileName);
            
            if (file.exists() && !file.isDirectory()) {
                try (FileInputStream fis = new FileInputStream(file)) {
                    byte[] data = new byte[(int) file.length()];
                    int bytesRead = fis.read(data);

                    if (bytesRead != -1) {
                        ctx.result(data, 200, "image/*");
                    } else {
                        ctx.status(404).result("File not found or empty.");
                    }
                } catch (IOException e) {
                    ctx.status(500).result("Internal server error: " + e.getMessage());
                }
            } else {
                ctx.status(404).result("File not found.");
            }
        });
    }
}
