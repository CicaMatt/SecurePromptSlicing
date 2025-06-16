import java.io.*;

public class HttpHelloPage {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String username = getUsernameFromRequest(request);
        writeResponseToClient(response, "Hello " + username);
    }

    private static String getUsernameFromRequest(InputStream request) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        while ((line = reader.readLine()) != null)
            if (line.startsWith("username="))
                return line.substring(9);
        return "";
    }

    private static void writeResponseToClient(OutputStream response, String content) throws IOException {
        PrintWriter writer = new PrintWriter(response);
        writer.write(content);
        writer.close();
    }
}