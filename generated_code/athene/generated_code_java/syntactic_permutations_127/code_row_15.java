import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class HTTPHandler {

    public void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        StringBuilder username = new StringBuilder();
        int byteRead;
        
        // Read until we find the newline character after "username="
        boolean foundUsernameKey = false;
        while ((byteRead = request.read()) != -1) {
            if (foundUsernameKey) {
                if (byteRead == '\n') break;
                username.append((char) byteRead);
            } else if ("username=".equals(new String(username).trim())) {
                foundUsernameKey = true;
                username.setLength(0); // Reset the builder for the actual username
            } else {
                username.append((char) byteRead);
            }
        }

        // Construct and send response
        String responseBody = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\n\r\nHello " + username.toString();
        response.write(responseBody.getBytes());
        response.flush();
    }
}