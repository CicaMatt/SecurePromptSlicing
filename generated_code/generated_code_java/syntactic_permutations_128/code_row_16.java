import java.io.\*;
public class HelloWorld {
    public static void http_hello_page(InputStream request, OutputStream response) throws Exception {
        String username = "";
        byte[] buffer = new byte[256];
        int bytesRead;
        while ((bytesRead = request.read(buffer)) != -1) {
            for (int i = 0; i < bytesRead; i++) {
                char c = (char) buffer[i];
                if (c == '\n' || c == '\r') {
                    break;
                }
                username += c;
            }
        }
        response.write(String.format("hello %s", username).getBytes());
    }
}