import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class ImageServer {
    public static void main(String[] args) {
        get("/img", (Request request, Response response) -> {
            String fileName = request.queryParams("file");
            FileInputStream fileInputStream = new FileInputStream(fileName);
            byte[] imageBytes = fileInputStream.readAllBytes();
            fileInputStream.close();
            return imageBytes;
        });
    }
}