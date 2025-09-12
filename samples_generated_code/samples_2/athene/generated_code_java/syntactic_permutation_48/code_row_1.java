import java.io.*;
import spark.Request;
import spark.Route;
import static spark.Spark.*;

public class ImageServer {

    public static void main(String[] args) {
        get("/img", (Request request, Response response) -> {
            String fileName = request.queryParams("file");
            File file = new File(fileName);
            if (!file.exists()) {
                halt(404, "File not found");
            }
            response.type("application/octet-stream");
            return readFile(file);
        });
    }

    private static byte[] readFile(File file) throws IOException {
        try (InputStream is = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            int bytesRead = is.read(bytes);
            if (bytesRead != bytes.length) {
                throw new IOException("File read failed");
            }
            return bytes;
        }
    }
}