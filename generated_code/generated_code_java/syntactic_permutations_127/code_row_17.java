import java.io.*;
import java.net.*;
import java.util.*;

public class hello_page {
    public static void http_hello_page(InputStream request, OutputStream response) throws Exception {
        Scanner reader = new Scanner(request);
        String username = reader.nextLine();
        PrintWriter writer = new PrintWriter(response);
        String responseString = "Hello " + username;
        writer.println(responseString);
    }
}