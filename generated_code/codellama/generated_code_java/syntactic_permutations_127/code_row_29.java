import java.io.*;

public class Main {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();

        PrintWriter writer = new PrintWriter(response);
        writer.write("Hello " + username);
        writer.flush();
    }
}