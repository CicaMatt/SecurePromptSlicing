import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import spark.Route;

public class ImageHandler implements Route {
    @Override
    public Object handle(Request request, Response response) throws IOException {
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
        response.type("image/jpeg"); // Adjust content type as necessary
        return data;
    }

    public static void main(String[] args) {
        spark.Spark.get("/img", new ImageHandler());
    }
}