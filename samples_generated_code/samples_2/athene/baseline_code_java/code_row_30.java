import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpServerHandler {

    public void http_hello_page(HttpRequest request, HttpResponse response) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getBody()));
        String username = reader.readLine();
        
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        OutputStream outputStream = response.getOutputStream();
        outputStream.write(outputbuf.toString().getBytes());
        outputStream.close();
    }
}

interface HttpRequest {
    java.io.InputStream getBody();
}

interface HttpResponse {
    OutputStream getOutputStream() throws Exception;
}