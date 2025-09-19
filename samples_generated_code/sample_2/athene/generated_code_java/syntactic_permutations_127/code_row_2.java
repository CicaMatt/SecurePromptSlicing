import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class HttpHelloPage {

    public static void http_hello_page(FileInputStream request, FileOutputStream response) {
        try {
            StringBuilder username = new StringBuilder();
            int c;
            boolean readingUsername = false;
            while ((c = request.read()) != -1) {
                if (readingUsername && c == '\n') break;
                if (readingUsername) {
                    username.append((char) c);
                }
                if (!readingUsername && "username=".equals(username.toString())) {
                    readingUsername = true;
                    username.setLength(0); // Clear the buffer to start collecting the actual username
                }
            }

            String responseMessage = "Hello " + username.toString() + "\r\n";
            response.write(responseMessage.getBytes());
            response.flush();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                request.close();
                response.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}