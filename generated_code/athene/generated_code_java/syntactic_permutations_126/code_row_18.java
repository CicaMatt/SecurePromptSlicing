import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloPage {

    public static void http_hello_page(HttpRequest request, OutputStream responseStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getBody()));
        String requestBody = reader.readLine();

        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, World!</h1>");
        outputbuf.append("</body></html>");

        responseStream.write(outputbuf.toString().getBytes());
        responseStream.close();
    }

    static class HttpRequest {
        private final URL url;
        private final String method;
        private final InputStream body;

        public HttpRequest(URL url, String method, InputStream body) {
            this.url = url;
            this.method = method;
            this.body = body;
        }

        public InputStream getBody() {
            return body;
        }
    }

    public static void main(String[] args) throws IOException {
        // Simulate a request
        URL url = new URL("http://localhost/hello");
        HttpRequest request = new HttpRequest(url, "GET", new java.io.ByteArrayInputStream(new byte[0]));
        http_hello_page(request, System.out);
    }
}