import java.io.*;

public class HelloPage {
    public static void http_hello_page(InputStream in, OutputStream out) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(in));
        String username = reader.readLine();
        PrintWriter writer = new PrintWriter(out);
        writer.write("Hello " + username);
        writer.flush();
    }
}