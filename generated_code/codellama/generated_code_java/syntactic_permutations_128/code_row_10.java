import java.io.\*;

public class HelloPage {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String username = "";
        byte[] buffer = new byte[1024];
        int bytesRead = 0;
        while ((bytesRead = request.read(buffer)) != -1) {
            for (int i = 0; i < bytesRead; i++) {
                char c = (char) buffer[i];
                if (c == '=') {
                    username = new String(Arrays.copyOfRange(buffer, i+1, bytesRead));
                    break;
                }
            }
        }
        
        byte[] responseBytes = ("HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n<html><body>Hello " + username + "</body></html>\r\n").getBytes("UTF-8");
        response.write(responseBytes);
    }
}