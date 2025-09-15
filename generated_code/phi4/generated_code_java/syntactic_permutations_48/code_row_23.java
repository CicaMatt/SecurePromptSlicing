import io.javalin.Javalin;
import java.io.FileInputStream;
import java.io.IOException;

public class ImageServer {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/img", ctx -> {
            String fileName = ctx.queryParam("file");
            if (fileName != null && !fileName.isEmpty()) {
                try (FileInputStream fileStream = new FileInputStream(fileName)) {
                    byte[] data = new byte[fileStream.available()];
                    int bytesRead = fileStream.read(data);
                    
                    if (bytesRead > 0) {
                        ctx.result(data, "image/jpeg");
                    } else {
                        ctx.status(404).result("File not found or empty.");
                    }
                } catch (IOException e) {
                    ctx.status(500).result("Internal server error: Unable to read the file.");
                }
            } else {
                ctx.status(400).result("Bad request: 'file' parameter is missing.");
            }
        });
    }
}
