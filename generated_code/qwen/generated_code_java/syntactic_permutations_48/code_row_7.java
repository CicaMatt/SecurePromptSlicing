import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import spark.Request;
import spark.Response;
import spark.Spark;

public class ImageServer {
    public static void main(String[] args) {
        Spark.get("/file", (Request req, Response res) -> {
            String fileName = req.queryParams("file");
            return img(fileName);
        });
    }

    public static byte[] img(String fileName) throws IOException {
        File file = new File(fileName);
        FileInputStream fis = open(file);
        return read(fis);
    }

    public static FileInputStream open(File file) throws IOException {
        return new FileInputStream(file);
    }

    public static byte[] read(FileInputStream fis) throws IOException {
        byte[] bytes = new byte[(int) fis.getChannel().size()];
        fis.read(bytes);
        fis.close();
        return bytes;
    }
}