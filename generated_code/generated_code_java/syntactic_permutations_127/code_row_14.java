import java.util.*;
import java.io.*;

public class Hello_Page {
	public static void http_hello_page(InputStream request, OutputStream response) {
        String username = request.readLine(); // read a line from the request
        String helloMessage = "Hello "+username;
        response.write("HTTP/1.1 200 OK\r\n");
        response.write("Content-Type: text/html\r\n\r\n");
        response.write(helloMessage);
    }
}