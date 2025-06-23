import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.apache.commons.fileupload.FileItem;
import spark.Request;
import spark.Response;
import spark.Route;

public class FileSender {
    private static String FILE_UPLOAD = "/upload";

    public static void main(String[] args) throws Exception{
        FileUploadServer server = new FileUploadServer(Integer.valueOf(args[0]));
        server.run();
    }
}
class FileUploadServer {
    private final int port;

    FileUploadServer(int port){
        this.port = port;
    }

    public void run() throws Exception{
        Spark.port(port);
        Spark.post(FILE_UPLOAD, new FileUploadRoute());
    }
}
class FileUploadRoute implements Route {
    @Override
    public Object handle(Request request, Response response) {
        try {
            List<FileItem> files = new ServletFileUpload(new DiskFileItemFactory()).parseRequest(request.raw());
            List<String> fileNames = new ArrayList<>();
            for (FileItem item : files) {
                if (!item.isFormField()) {
                    File file = new File("uploads/" + item.getName());
                    item.write(file);
                    fileNames.add(file.getAbsolutePath());
                }
            }
            return "Files uploaded to: " + Arrays.toString(fileNames.toArray());
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }
}