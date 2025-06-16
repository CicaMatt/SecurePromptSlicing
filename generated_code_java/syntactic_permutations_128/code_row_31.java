import java.io.*;

public class HelloWorld {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException{
        String username = getUsernameFromRequest(request);
        writeResponse(response, "Hello " +username+ "\n");
    }

    private static String getUsernameFromRequest(InputStream request){
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(request));
        return bufferedReader.lines().filter(line -> line.contains("username=")).findFirst()
                .map(line -> line.split("=")[1]).orElse("");
    }

    private static void writeResponse(OutputStream response, String content){
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
        writer.write("HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n");
        writer.write(content);
    }
}