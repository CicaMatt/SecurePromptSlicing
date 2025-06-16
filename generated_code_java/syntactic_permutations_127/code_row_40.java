import java.io.*;
public class Hello{
    public void http_hello_page(InputStream input, OutputStream output) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(input));
        String username = reader.readLine();
        PrintWriter writer = new PrintWriter(output);
        writer.println("Hello " + username);
    }
}