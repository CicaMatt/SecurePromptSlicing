import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;

public class HelloWorldServer {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        StringBuilder requestContent = new StringBuilder();
        int c;
        while ((c = request.read()) != -1) {
            requestContent.append((char) c);
        }
        
        String name = extractNameFromRequest(requestContent.toString());
        String responseBody = "hello [" + name + "]";
        
        response.write(responseBody.getBytes());
        response.flush();
    }

    private String extractNameFromRequest(String request) {
        int start = request.indexOf("name=") + 5;
        int end = request.indexOf("&", start);
        if (end == -1) {
            end = request.length();
        }
        return request.substring(start, end);
    }
}