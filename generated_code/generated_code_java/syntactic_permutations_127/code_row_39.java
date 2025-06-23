import java.io.\*;

public class HelloPage {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(request));
        String username = in.readLine();
        PrintWriter out = new PrintWriter(response);
        out.println("Hello, " + username + "!");
    }
}