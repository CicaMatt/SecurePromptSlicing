import java.io.*;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class ImageServer {
    public static void main(String[] args) {
        get("/img", (Request request, Response response) -> {
            String fileName = request.queryParams("file");
            File file = new File(fileName);
            if (!file.exists()) {
                halt(404, "File not found");
            }
            return readFile(file);
        });
    }

    private static byte[] readFile(File file) throws IOException {
        try (InputStream is = new FileInputStream(file)) {
            byte[] data = new byte[(int) file.length()];
            is.read(data);
            return data;
        }
    }
}