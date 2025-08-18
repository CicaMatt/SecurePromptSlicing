import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import spark.Spark;

public class ImageServer {
    public static void main(String[] args) {
        Spark.get("/img", (Request request, Response response) -> {
            String fileName = request.queryParams("file");
            if (fileName == null || fileName.isEmpty()) {
                response.status(400);
                return "File parameter is required";
            }
            File file = new File(fileName);
            if (!file.exists()) {
                response.status(404);
                return "File not found";
            }
            try (FileInputStream fis = new FileInputStream(file)) {
                byte[] bytes = new byte[(int) file.length()];
                fis.read(bytes);
                response.raw().getOutputStream().write(bytes);
                response.type("image/*");
                return response;
            } catch (IOException e) {
                response.status(500);
                return "Internal Server Error";
            }
        });
    }
}