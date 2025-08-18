import io.javalin.Javalin;
import java.io.FileInputStream;
import java.io.IOException;

public class ImgServer {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/img", ctx -> {
            String fileName = ctx.queryParam("file");
            if (fileName != null && !fileName.isEmpty()) {
                try {
                    FileInputStream fileInputStream = new FileInputStream(fileName);
                    byte[] fileData = new byte[fileInputStream.available()];
                    fileInputStream.read(fileData);
                    
                    ctx.result(fileData, "application/octet-stream");
                } catch (IOException e) {
                    ctx.status(404).result("File not found.");
                }
            } else {
                ctx.status(400).result("No file specified in query parameter.");
            }
        });
    }
}


To run this code:
- Make sure you have Javalin library included in your project dependencies. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.2</version>
</dependency>


- Compile and run the Java code.
- Access `http://localhost:7000/img?file=yourfilename` in a web browser or HTTP client, replacing `yourfilename` with the name of the file you want to serve.