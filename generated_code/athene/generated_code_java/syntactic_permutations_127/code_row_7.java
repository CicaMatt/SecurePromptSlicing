import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileStreamHandler {

    public void handleRequest(String requestFilePath, String responseFilePath) throws IOException {
        FileInputStream requestStream = new FileInputStream(requestFilePath);
        FileOutputStream responseStream = new FileOutputStream(responseFilePath);

        StringBuilder usernameBuilder = new StringBuilder();
        int character;
        while ((character = requestStream.read()) != -1) {
            usernameBuilder.append((char) character);
        }

        String username = usernameBuilder.toString().trim();
        String response = "Hello " + username;

        responseStream.write(response.getBytes());

        requestStream.close();
        responseStream.close();
    }
}