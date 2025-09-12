import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class ImgServer {

    public static void main(String[] args) {
        Spark.get("/img", new ImgRoute(), "image/*");
    }

    static class ImgRoute implements Route {
        @Override
        public Object handle(Request request, Response response) throws Exception {
            String fileName = request.queryParams("file");

            if (fileName == null || fileName.isEmpty()) {
                response.status(400);
                return "File parameter is missing in the URL.";
            }

            File file = new File(fileName);

            if (!file.exists() || !file.canRead()) {
                response.status(404);
                return "File not found or cannot be read.";
            }

            try (FileInputStream fis = new FileInputStream(file)) {
                byte[] data = new byte[(int) file.length()];
                int bytesRead = fis.read(data);

                if (bytesRead != -1) {
                    response.type("application/octet-stream");
                    OutputStream outputStream = response.raw().getOutputStream();
                    outputStream.write(data);
                    outputStream.flush();
                    return null;
                }
            } catch (IOException e) {
                response.status(500);
                return "Internal server error: " + e.getMessage();
            }

            response.status(400);
            return "Error reading file.";
        }
    }
}


Make sure to include the Spark Java library in your project dependencies. For example, if you're using Maven, add:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


If you're using another dependency management tool, adjust accordingly to include Spark Java.