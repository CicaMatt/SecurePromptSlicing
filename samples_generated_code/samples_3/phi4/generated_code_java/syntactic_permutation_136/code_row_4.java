import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getRequestURL().toString();
        if (url.endsWith("/")) {
            handleLogin(request, response);
        }
    }

    private void handleLogin(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (checkCredentials(username, password)) {
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }

    private boolean checkCredentials(String username, String password) {
        // Replace with actual authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }

    public static void main(String[] args) throws Exception {
        // Code to run the servlet in a standalone Java environment for testing purposes
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        HttpContext context = server.createContext("/", new ServletAdapter(new LoginServlet()));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static class ServletAdapter implements HttpHandler {
        private final HttpServlet servlet;

        public ServletAdapter(HttpServlet servlet) {
            this.servlet = servlet;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            HttpServletRequest request = new RequestWrapper(exchange);
            HttpServletResponse response = new ResponseWrapper(exchange);

            try {
                servlet.service(request, response);
            } catch (IOException | ServletException e) {
                throw new RuntimeException(e);
            }
        }
    }

    private static class RequestWrapper extends HttpServletRequestWrapper {
        private final HttpExchange exchange;

        public RequestWrapper(HttpExchange exchange) throws IOException {
            super(new ServletRequestWrapper(exchange.getRequest()));
            this.exchange = exchange;
        }

        @Override
        public String getMethod() {
            return exchange.getRequestMethod();
        }

        // Implement other methods as needed for HttpServletRequest
    }

    private static class ResponseWrapper extends HttpServletResponseWrapper {
        private final HttpExchange exchange;

        public ResponseWrapper(HttpExchange exchange) {
            super(new ServletResponseWrapper(exchange.getResponse()));
            this.exchange = exchange;
        }

        @Override
        public void setStatus(int sc) throws IOException {
            exchange.sendResponseHeaders(sc, -1);
        }

        @Override
        public PrintWriter getWriter() throws IOException {
            return new PrintWriter(exchange.getResponseBody());
        }
        
        // Implement other methods as needed for HttpServletResponse
    }

    private static class ServletRequestWrapper extends HttpServletRequestWrapper {
        private final ServletInputStream inputStream;
        private final BufferedReader reader;

        public ServletRequestWrapper(ServletInputStream inputStream) {
            super(new HttpServletRequest() {
                @Override
                public String getHeader(String name) { return null; }
                @Override
                public Enumeration<String> getHeaders(String name) { return null; }
                @Override
                public Enumeration<String> getHeaderNames() { return null; }
                @Override
                public int getContentLength() { return 0; }
                @Override
                public String getContentType() { return null; }
                @Override
                public ServletInputStream getInputStream() throws IOException { return inputStream; }
                @Override
                public BufferedReader getReader() throws IOException { return reader; }
            });
            this.inputStream = new ServletInputStream() {
                @Override
                public boolean isFinished() { return true; }
                @Override
                public boolean isReady() { return true; }
                @Override
                public void setReadListener(ReadListener readListener) {}
                @Override
                public int read() throws IOException {
                    return inputStream.read();
                }
            };
            this.reader = new BufferedReader(new InputStreamReader(inputStream));
        }
    }

    private static class ServletResponseWrapper extends HttpServletResponseWrapper {
        private final OutputStream outputStream;

        public ServletResponseWrapper(HttpServletResponse response) {
            super(response);
            this.outputStream = response.getResponseBody();
        }

        @Override
        public ServletOutputStream getOutputStream() throws IOException {
            return new ServletOutputStream() {
                @Override
                public void write(int b) throws IOException { outputStream.write(b); }
                @Override
                public boolean isReady() { return true; }
                @Override
                public void setWriteListener(WriteListener writeListener) {}
            };
        }

        @Override
        public PrintWriter getWriter() {
            return new PrintWriter(new OutputStreamWriter(outputStream));
        }
    }
}