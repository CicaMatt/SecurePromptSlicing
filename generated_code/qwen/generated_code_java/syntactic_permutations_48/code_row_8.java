import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class ImageServer {

    public static void main(String[] args) {
        Spark.get("/img", (request, response) -> img(request, response));
    }

    private static Object img(Request request, Response response) throws IOException {
        String fileName = request.queryParams("file");
        if (fileName == null || fileName.isEmpty()) {
            response.status(400);
            return "Missing file parameter";
        }
        
        File file = new File(fileName);
        if (!file.exists() || !file.isFile()) {
            response.status(404);
            return "File not found";
        }

        byte[] bytes = Files.readAllBytes(Paths.get(file.getAbsolutePath()));
        response.type("image/" + getFileExtension(fileName));
        return bytes;
    }

    private static String getFileExtension(String fileName) {
        int lastIndexOf = fileName.lastIndexOf(".");
        if (lastIndexOf == -1) {
            return "";
        }
        return fileName.substring(lastIndexOf + 1);
    }
}