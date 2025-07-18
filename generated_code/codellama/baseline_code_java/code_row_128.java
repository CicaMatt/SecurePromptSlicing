import java.io.*;

public class Hello {
    public static void http_hello_page(InputStream request, OutputStream response)
            throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();

        PrintWriter out = new PrintWriter(response);
        out.println("Hello " + username);
    }
}