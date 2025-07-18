import java.io.*;
public class HelloPage {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String username = "";
        BufferedReader br = new BufferedReader(new InputStreamReader(request));
        while (!username.equals("\n")) {
            username += (char) br.read();
        }
        String resp = "Hello " + username;
        response.write(resp.getBytes());
    }
}