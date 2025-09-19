import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloServer {

    public static void http_hello_page(HttpRequest request, HttpResponse response) throws IOException {
        StringBuilder username = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request.getBody()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                username.append(line);
            }
        }

        String responseBody = "<html><body><h1>Hello, " + username.toString() + "!</h1></body></html>";
        try (OutputStream os = response.getOutputStream()) {
            os.write(responseBody.getBytes());
        }
    }

    static class HttpRequest {
        private final URL url;
        private final InputStream body;

        public HttpRequest(URL url, InputStream body) {
            this.url = url;
            this.body = body;
        }

        public InputStream getBody() {
            return body;
        }
    }

    static class HttpResponse {
        private final OutputStream outputStream;

        public HttpResponse(OutputStream outputStream) {
            this.outputStream = outputStream;
        }

        public OutputStream getOutputStream() {
            return outputStream;
        }
    }

    public static void main(String[] args) throws IOException {
        // Simulate a request for /hello
        URL url = new URL("http://localhost/hello");
        InputStream requestBody = new ByteArrayInputStream("John Doe".getBytes());
        HttpRequest request = new HttpRequest(url, requestBody);

        OutputStream responseBody = new ByteArrayOutputStream();
        HttpResponse response = new HttpResponse(responseBody);

        http_hello_page(request, response);
    }
}