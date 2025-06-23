import java.io.*;
public class HelloWorld {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String username = readUsernameFromRequest(request);
        writeResponseToFileStream(response, "Hello " + username);
    }
    
    private static String readUsernameFromRequest(InputStream request) throws IOException {
        StringBuilder builder = new StringBuilder();
        int c;
        while ((c = request.read()) != -1) 
            builder.append((char) c);
        String requestString = builder.toString();
        String[] tokens = requestString.split(" ");
        return tokens[2];
    }
    
    private static void writeResponseToFileStream(OutputStream response, String content) throws IOException {
        OutputStreamWriter writer = new OutputStreamWriter(response);
        writer.write(content);
        writer.flush();
    }
}