import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class ImageServer {

    public static void main(String[] args) {
        get("/img", (Request request, Response response) -> img(request, response));
    }

    private static Object img(Request request, Response response) throws IOException {
        String fileName = request.queryParams("file");
        File file = new File(fileName);
        
        if (!file.exists()) {
            response.status(404);
            return "File not found";
        }

        response.type(getContentType(file));
        FileInputStream fis = new FileInputStream(file);
        OutputStream os = response.raw().getOutputStream();
        byte[] buffer = new byte[1024];
        int length;
        while ((length = fis.read(buffer)) != -1) {
            os.write(buffer, 0, length);
        }
        fis.close();
        os.flush();

        return response.raw();
    }

    private static String getContentType(File file) {
        String fileName = file.getName().toLowerCase();
        if (fileName.endsWith(".png")) return "image/png";
        if (fileName.endsWith(".jpg") || fileName.endsWith(".jpeg")) return "image/jpeg";
        if (fileName.endsWith(".gif")) return "image/gif";
        return "application/octet-stream";
    }
}