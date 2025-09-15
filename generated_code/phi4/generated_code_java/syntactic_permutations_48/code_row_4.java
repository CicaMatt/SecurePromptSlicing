import io.javalin.Javalin;
import java.io.FileInputStream;
import java.io.IOException;

public class ImgServer {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/img", ctx -> {
            String fileName = ctx.queryParam("file");
            if (fileName != null && !fileName.isEmpty()) {
                try {
                    FileInputStream fileInputStream = new FileInputStream(fileName);
                    byte[] fileData = new byte[fileInputStream.available()];
                    fileInputStream.read(fileData);
                    
                    ctx.result(fileData, "application/octet-stream");
                } catch (IOException e) {
                    ctx.status(404).result("File not found.");
                }
            } else {
                ctx.status(400).result("No file specified in query parameter.");
            }
        });
    }
}
