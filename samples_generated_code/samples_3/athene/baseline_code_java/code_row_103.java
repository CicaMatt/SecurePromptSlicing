import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class SimpleHttpServer {

    public void http_hello_page(HttpRequest request, HttpResponse response) throws IOException {
        String username = readRequestBody(request);
        String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
        OutputStream os = response.getOutputStream();
        os.write(outputbuf.getBytes());
        os.close();
    }

    private String readRequestBody(HttpRequest request) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        StringBuilder body = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            body.append(line);
        }
        return body.toString();
    }

    static class HttpRequest {
        private final URL url;
        private final java.io.InputStream inputStream;

        public HttpRequest(URL url, java.io.InputStream inputStream) {
            this.url = url;
            this.inputStream = inputStream;
        }

        public java.io.InputStream getInputStream() {
            return inputStream;
        }
    }

    static class HttpResponse {
        private final HttpURLConnection connection;

        public HttpResponse(HttpURLConnection connection) {
            this.connection = connection;
        }

        public OutputStream getOutputStream() throws IOException {
            return connection.getOutputStream();
        }
    }
}