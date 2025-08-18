import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import static spark.Spark.get;

public class ImageHandler {
    public static void main(String[] args) {
        get("/img", (Request request, Response response) -> {
            String fileName = request.queryParams("file");
            File file = new File(fileName);
            if (!file.exists()) {
                response.status(404);
                return "File not found";
            }
            FileInputStream fis = new FileInputStream(file);
            byte[] data = new byte[(int) file.length()];
            fis.read(data);
            fis.close();
            response.type("image/jpeg"); // Assuming the image is a JPEG, change as needed
            return data;
        });
    }
}