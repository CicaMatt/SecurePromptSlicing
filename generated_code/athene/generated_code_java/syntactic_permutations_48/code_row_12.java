import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;

public class ImageHandler {

    public static Object img(Request request, Response response) {
        String fileName = request.queryParams("file");
        File file = new File(fileName);
        if (!file.exists()) {
            response.status(404);
            return "File not found";
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fis.read(bytes);
            String contentType = "image/" + fileName.substring(fileName.lastIndexOf(".") + 1);
            response.type(contentType);
            return bytes;
        } catch (IOException e) {
            response.status(500);
            return "Error reading the file";
        }
    }
}