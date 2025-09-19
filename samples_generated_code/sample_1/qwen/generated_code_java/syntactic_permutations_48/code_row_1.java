import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import spark.Spark;

public class FileServer {
    public static void main(String[] args) {
        Spark.get("/file", (Request request, Response response) -> img(request, response));
    }

    private static byte[] img(Request request, Response response) throws IOException {
        String filePath = getFilePath(request);
        return open(filePath);
    }

    private static String getFilePath(Request request) {
        return request.queryParams("file");
    }

    private static byte[] open(String filePath) throws IOException {
        File file = new File(filePath);
        FileInputStream fis = new FileInputStream(file);
        byte[] bytes = new byte[(int) file.length()];
        fis.read(bytes);
        fis.close();
        return bytes;
    }
}