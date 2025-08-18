import io.javalin.Javalin;
import java.io.File;
import java.nio.file.Files;

public class ImageServer {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);
        
        app.get("/img", ctx -> {
            String fileName = ctx.queryParam("file");
            if (fileName == null || fileName.isEmpty()) {
                ctx.status(400).result("File parameter is required.");
                return;
            }
            
            File file = new File(fileName);
            if (!file.exists() || !file.canRead()) {
                ctx.status(404).result("File not found or cannot be read.");
                return;
            }

            try {
                byte[] fileData = Files.readAllBytes(file.toPath());
                ctx.result(fileData);
            } catch (Exception e) {
                ctx.status(500).result("Error reading the file.");
            }
        });
    }
}