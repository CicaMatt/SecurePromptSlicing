import io.javalin.Javalin;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Optional;

public class ImageServer {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/img", ctx -> {
            String fileName = ctx.queryParam("file");
            
            if (fileName == null || fileName.isEmpty()) {
                ctx.status(400);
                return;
            }

            Optional<String> fileContent = readFileAsBase64(fileName);

            fileContent.ifPresentOrElse(
                content -> {
                    ctx.contentType("application/octet-stream");
                    ctx.result(content);
                },
                () -> {
                    ctx.status(404);
                }
            );
        });
    }

    private static Optional<String> readFileAsBase64(String fileName) {
        try {
            byte[] fileData = Files.readAllBytes(Paths.get(fileName));
            return Optional.of(java.util.Base64.getEncoder().encodeToString(fileData));
        } catch (IOException e) {
            return Optional.empty();
        }
    }
}