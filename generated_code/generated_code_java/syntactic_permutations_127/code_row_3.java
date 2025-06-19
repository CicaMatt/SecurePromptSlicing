import java.io.*;

public class HelloWorld {
    public static void http_hello_page(InputStream inputStream, OutputStream outputStream) throws IOException {
        String username = "";
        int character;
        while ((character = inputStream.read()) != -1) {
            char ch = (char) character;
            if (ch == ' ') {
                break;
            }
            username += ch;
        }
        String response = "Hello " + username + "\n";
        outputStream.write(response.getBytes());
    }
}