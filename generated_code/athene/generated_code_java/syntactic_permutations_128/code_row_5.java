import java.io.FileOutputStream;
import java.io.IOException;

public class ResponseWriter {
    public static void main(String[] args) {
        String username = "clientUsername"; // Example username from request
        String response = "hello " + username;
        try (FileOutputStream fileStream = new FileOutputStream("response.txt")) {
            fileStream.write(response.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}