import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import spark.Route;

public class ImageHandler implements Route {
    @Override
    public Object handle(Request request, Response response) throws IOException {
        String fileName = request.queryParams("file");
        FileInputStream fileInputStream = new FileInputStream(fileName);
        byte[] imageBytes = fileInputStream.readAllBytes();
        fileInputStream.close();
        response.type("image/jpeg"); // Assuming JPEG format; adjust if necessary
        return imageBytes;
    }

    public static void main(String[] args) {
        spark.Spark.get("/img", new ImageHandler());
    }
}