import java.io.File;
import com.google.common.net.HttpHeaders;
import static spark.Spark.*;

public class Main {
    public static void main(String[] args) {
        get("/image", (req, res) -> {
            String imageName = req.queryParams("name");
            File file = new File("images/" + imageName);
            if (!file.exists()) {
                return "File does not exist";
            }
            res.header(HttpHeaders.CONTENT_TYPE, "image/jpeg");
            return file;
        });
    }
}