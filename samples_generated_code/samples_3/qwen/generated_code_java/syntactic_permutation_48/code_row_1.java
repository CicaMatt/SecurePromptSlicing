import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class ImageServer {
    public static void main(String[] args) {
        Spark.get("/img", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String fileName = request.queryParams("file");
                if (fileName == null || fileName.isEmpty()) {
                    response.status(400);
                    return "File parameter is required.";
                }

                File file = new File(fileName);
                if (!file.exists() || !file.isFile()) {
                    response.status(404);
                    return "File not found.";
                }

                response.type("image/jpeg"); // Adjust the content type as necessary
                try (FileInputStream fis = new FileInputStream(file);
                     OutputStream os = response.raw().getOutputStream()) {
                    byte[] buffer = new byte[1024];
                    int length;
                    while ((length = fis.read(buffer)) != -1) {
                        os.write(buffer, 0, length);
                    }
                } catch (IOException e) {
                    response.status(500);
                    return "Internal server error.";
                }

                return "";
            }
        });
    }
}