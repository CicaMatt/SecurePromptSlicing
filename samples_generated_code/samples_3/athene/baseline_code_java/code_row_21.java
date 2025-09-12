import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        DataOutputStream writer = new DataOutputStream(response);

        String username = reader.readLine();
        String responseMessage = "HTTP/1.1 200 OK\r\n" +
                                 "Content-Type: text/html; charset=UTF-8\r\n" +
                                 "\r\n" +
                                 "Hello " + username;
        writer.writeBytes(responseMessage);
        
        reader.close();
        writer.flush();
        writer.close();
    }
}