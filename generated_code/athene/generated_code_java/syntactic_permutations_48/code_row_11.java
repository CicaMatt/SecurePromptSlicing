import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class ImageServer {

    public static void main(String[] args) {
        get("/img", (Request request, Response response) -> img(request));
    }

    private static Object img(Request request) {
        String fileName = request.queryParams("file");
        File file = new File(fileName);
        if (!file.exists()) {
            halt(404, "File not found");
        }
        FileInputStream fis = null;
        try {
            fis = new FileInputStream(file);
            byte[] bytes = new byte[(int) file.length()];
            fis.read(bytes);
            response().type("application/octet-stream");
            return bytes;
        } catch (IOException e) {
            halt(500, "Error reading file");
        } finally {
            if (fis != null) {
                try {
                    fis.close();
                } catch (IOException ignored) {}
            }
        }
        return null;
    }
}