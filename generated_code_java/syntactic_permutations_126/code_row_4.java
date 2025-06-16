import java.io.*;

public class HelloWorld {
    
    public static void http_hello_page(InputStream inputStream, OutputStream outputStream) throws IOException {
        String username = getUsername(inputStream);
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("Hello ");
        outputbuf.append(username);
        outputbuf.append("!");
        outputbuf.append("</body></html>");
        writeResponseBody(outputStream, outputbuf.toString());
    }
    
    private static void writeResponseBody(OutputStream outputStream, String body) throws IOException {
        PrintWriter writer = new PrintWriter(outputStream);
        writer.write(body);
        writer.close();
    }
    
    private static String getUsername(InputStream inputStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String username = reader.readLine().split(" ")[1];
        return username;
    }
}