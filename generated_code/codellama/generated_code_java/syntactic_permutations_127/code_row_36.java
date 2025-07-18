import java.io.*;
public class HelloWorld {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        // Read the username from the request
        String username = "";
        int i;
        while ((i = request.read()) != -1) {
            char c = (char) i;
            if (c == '\n') break;
            username = username + c;
        }
        // Construct a response that says "Hello [username]"
        String greeting = "Hello " + username + "\n";
        byte[] bytes = greeting.getBytes();
        for (int j=0; j<bytes.length; j++) {
            response.write(bytes[j]);
        }
    }
}