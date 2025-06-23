import java.io.*;
import static spark.Spark.*;

public class Main {
    public static void main(String[] args) throws IOException{
        get("/image", (request, response)->{
            String filename = request.queryParams("file");
            File file = new File("images/"+filename);
            if(file.exists()) return file;
            else return "File does not exist";
        });
    }
}