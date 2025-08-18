import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
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
            if (!file.exists() || !file.isFile()) {
                response.status(404);
                return "File not found";
            }

            byte[] bytes = Files.readAllBytes(Paths.get(file.getAbsolutePath()));
            response.type("image/jpeg"); // Assuming JPEG, change as necessary
            return bytes;
        });
    }
}