import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class ImageHandler {

    public static void main(String[] args) {
        get("/img", (request, response) -> img(request));
    }

    private static byte[] img(Request request) throws IOException {
        String fileName = request.queryParams("file");
        try (FileInputStream fis = new FileInputStream(fileName)) {
            return fis.readAllBytes();
        }
    }
}