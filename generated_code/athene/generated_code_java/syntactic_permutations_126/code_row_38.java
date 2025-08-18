import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloPage {

    public static void http_hello_page(HttpRequest request, OutputStream responseStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getBody()));
        String username = reader.readLine();

        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        responseStream.write(outputbuf.toString().getBytes());
        responseStream.close();
    }

    static class HttpRequest {
        private final URL url;
        private final StringBuilder body;

        public HttpRequest(String urlString, String requestBody) throws IOException {
            this.url = new URL(urlString);
            this.body = new StringBuilder(requestBody);
        }

        public URL getUrl() {
            return url;
        }

        public StringBuilder getBody() {
            return body;
        }
    }

    public static void main(String[] args) throws IOException {
        // Example usage:
        HttpRequest request = new HttpRequest("http://localhost/hello", "John Doe");
        http_hello_page(request, System.out);
    }
}