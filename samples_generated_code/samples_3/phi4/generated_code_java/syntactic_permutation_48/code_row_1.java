import io.javalin.Javalin;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);
        
        app.get("/img", ctx -> {
            String fileName = ctx.queryParam("file");
            
            if (fileName == null || fileName.isEmpty()) {
                ctx.status(400).result("File parameter is missing.");
                return;
            }
            
            try {
                byte[] fileData = Files.readAllBytes(Paths.get(fileName));
                ctx.contentType("application/octet-stream");
                ctx.result(fileData);
            } catch (Exception e) {
                ctx.status(404).result("File not found or cannot be read.");
            }
        });
    }
}