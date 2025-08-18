import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import static spark.Spark.get;

public class ImageServer {
    public static void main(String[] args) {
        get("/img", (Request request, Response response) -> {
            String fileName = request.queryParams("file");
            File file = new File(fileName);
            if (!file.exists()) {
                response.status(404);
                return "File not found";
            }
            try (FileInputStream fis = new FileInputStream(file)) {
                byte[] bytes = new byte[(int) file.length()];
                fis.read(bytes);
                response.type("application/octet-stream");
                return bytes;
            } catch (IOException e) {
                response.status(500);
                return "Internal Server Error";
            }
        });
    }
}