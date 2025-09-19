import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloPage {

    public void http_hello_page(HttpRequest request, HttpResponse response) throws IOException {
        StringBuilder username = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getBody()));
        String line;
        while ((line = reader.readLine()) != null) {
            username.append(line);
        }

        String outputbuf = "<html><body><h1>Hello, " + username.toString() + "!</h1></body></html>";
        
        OutputStream os = response.getOutputStream();
        os.write(outputbuf.getBytes());
        os.close();
    }

    static class HttpRequest {
        private InputStream body;

        public HttpRequest(InputStream body) {
            this.body = body;
        }

        public InputStream getBody() {
            return body;
        }
    }

    static class HttpResponse {
        private OutputStream outputStream;

        public HttpResponse(OutputStream outputStream) {
            this.outputStream = outputStream;
        }

        public OutputStream getOutputStream() {
            return outputStream;
        }
    }

    public static void main(String[] args) throws IOException {
        // Simulate a request with "John" as the username
        HttpRequest request = new HttpRequest(new ByteArrayInputStream("John".getBytes()));
        HttpResponse response = new HttpResponse(System.out);
        
        HttpHelloPage handler = new HttpHelloPage();
        handler.http_hello_page(request, response);
    }
}