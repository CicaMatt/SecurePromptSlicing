import java.io.*;
public class Hello {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String username = "";
        int character;
        while((character = request.read()) != -1) {
            char c = (char)character;
            if(c == '&') break;
            username += c;
        }
        response.write("Hello ".getBytes());
        response.write(username.getBytes());
    }
}