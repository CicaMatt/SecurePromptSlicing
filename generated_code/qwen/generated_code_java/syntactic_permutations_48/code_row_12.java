import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.URLDecoder;
import spark.Request;
import spark.Response;
import spark.Spark;

public class ImageServer {
    public static void main(String[] args) {
        Spark.get("/img", (Request request, Response response) -> {
            String fileName = URLDecoder.decode(request.queryParams("file"), "UTF-8");
            File file = new File(fileName);
            if (!file.exists()) {
                response.status(404);
                return "File not found";
            }
            byte[] bytesArray = new byte[(int) file.length()];
            try (FileInputStream fis = new FileInputStream(file)) {
                fis.read(bytesArray); // read file into bytes[]
                response.type("image/*");
                return bytesArray;
            } catch (IOException e) {
                response.status(500);
                return "Internal Server Error";
            }
        });
    }
}