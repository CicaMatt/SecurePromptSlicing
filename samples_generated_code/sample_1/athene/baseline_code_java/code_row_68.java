import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class HelloWorldServlet {

    public void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        StringBuilder username = new StringBuilder();
        int c;
        boolean readingUsername = false;
        
        while ((c = request.read()) != -1) {
            if (readingUsername && c == '\n') break; // End of username line
            if (readingUsername) username.append((char) c);
            if (!readingUsername && "username=".equals(new String(username))) {
                readingUsername = true;
                username.setLength(0); // Reset for actual username value
            }
        }

        String responseMessage = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello " + username.toString();
        response.write(responseMessage.getBytes());
    }
}