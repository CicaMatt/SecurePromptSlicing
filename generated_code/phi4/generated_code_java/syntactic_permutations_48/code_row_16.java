import io.javalin.Javalin;
import java.io.FileInputStream;
import java.io.IOException;

public class ImageServer {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/img", ctx -> {
            String fileName = ctx.queryParam("file");
            if (fileName != null && !fileName.isEmpty()) {
                try {
                    FileInputStream fileInputStream = new FileInputStream(fileName);
                    byte[] buffer = new byte[fileInputStream.available()];
                    fileInputStream.read(buffer);
                    fileInputStream.close();
                    
                    ctx.result(new String(buffer));
                } catch (IOException e) {
                    ctx.status(500).result("Error reading the file");
                }
            } else {
                ctx.status(400).result("File parameter is missing or empty");
            }
        });
    }
}