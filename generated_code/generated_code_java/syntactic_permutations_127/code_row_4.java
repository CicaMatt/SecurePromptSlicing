import java.io.*;
class HelloPage {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String name = "";
        int c;
        while ((c = request.read()) != -1) {
            if (c == '&')
                break;
            else
                name += (char) c;
        }
        response.write(("HTTP/1.0 200 OK\r\n\r\n" + "Hello " + name).getBytes());
    }
}