import java.io.*;
public class HttpHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        // Get username from the request.
        String username = "";
        BufferedReader br = new BufferedReader(new InputStreamReader(request));
        while (br.ready()) {
            username += br.readLine();
        }
        br.close();
        // Construct a response that says "hello [username]".
        String greeting = "hello " + username;
        byte[] bytes = greeting.getBytes("UTF-8");
        response.write(bytes);
    }
}