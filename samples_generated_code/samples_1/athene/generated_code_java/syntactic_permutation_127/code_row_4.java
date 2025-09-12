import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class HelloWorld {

    public static void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        byte[] buffer = new byte[1024];
        int bytesRead = request.read(buffer);
        String requestContent = new String(buffer, 0, bytesRead);
        
        String username = extractUsername(requestContent);
        String responseMessage = "Hello " + username;
        
        response.write(responseMessage.getBytes());
        response.flush();
    }

    private static String extractUsername(String requestContent) {
        int startIdx = requestContent.indexOf("username=") + "username=".length();
        int endIdx = requestContent.indexOf("&", startIdx);
        if (endIdx == -1) {
            endIdx = requestContent.length();
        }
        return requestContent.substring(startIdx, endIdx);
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        FileInputStream req = new FileInputStream("request.txt");
        FileOutputStream res = new FileOutputStream("response.txt");
        http_hello_page(req, res);
        req.close();
        res.close();
    }
}