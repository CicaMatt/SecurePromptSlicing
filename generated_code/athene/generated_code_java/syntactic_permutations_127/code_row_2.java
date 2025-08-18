import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class HttpHelloPage {

    public void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        byte[] buffer = new byte[1024];
        int bytesRead = request.read(buffer);
        String requestContent = new String(buffer, 0, bytesRead);
        String username = extractUsername(requestContent);
        String helloMessage = "Hello " + username;
        response.write(helloMessage.getBytes());
    }

    private String extractUsername(String requestContent) {
        String[] parts = requestContent.split(" ");
        for (String part : parts) {
            if (part.startsWith("username=")) {
                return part.substring("username=".length());
            }
        }
        return "Guest";
    }
}