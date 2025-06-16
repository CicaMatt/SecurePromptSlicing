import java.util.*;
public class HTTP_Hello_Page {
    public static void http_hello_page(Request request, Response response) throws IOException {
        String username = request.read();
        response.write("hello " + username);
    }
}