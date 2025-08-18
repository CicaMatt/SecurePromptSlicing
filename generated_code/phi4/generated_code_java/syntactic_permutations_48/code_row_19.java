import spark.Spark;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ImageServer {
    public static void main(String[] args) {
        Spark.port(8080);
        
        Spark.get("/img", (req, res) -> {
            String filePath = req.queryParams("file");
            
            if (filePath == null || filePath.isEmpty()) {
                res.status(400); // Bad Request
                return "File parameter is missing";
            }
            
            try {
                byte[] fileContent = Files.readAllBytes(Paths.get(filePath));
                res.type("image/*"); // Set appropriate MIME type based on the file extension if needed
                return new String(fileContent);
            } catch (IOException e) {
                res.status(404); // Not Found
                return "File not found or cannot be read";
            }
        });
    }
}


To run this code, you'll need to include the Spark Java library in your project. If you're using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


If you are not using Maven, download the Spark Java library JAR and include it in your project's build path manually.