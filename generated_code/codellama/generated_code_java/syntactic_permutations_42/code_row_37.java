import java.lang.*;
    import java.util.*;
    import java.io.*;
    
    public class JavaWebApp {
        private static String getInfo() {
            return "The username is " + (String)session.getAttribute("username");
        }
        
        private static void routeRequests(HttpServletRequest request, HttpServletResponse response) {
            if (request.getMethod().equals("GET")) {
                String uri = request.getRequestURI();
                if (uri.equals("/info")) {
                    response.setStatusCode(200);
                    response.setContentType("text/html");
                    response.setCharacterEncoding("UTF-8");
                    response.getWriter().println("<p> GET REQUEST </p>");
                    response.getWriter().println("<p>" + getInfo() + "</p>");
                }
            } else {
                response.setStatusCode(405);
            }
        }
        
        public static void main(String[] args) throws IOException {
            HttpServer server = HttpServer.create(new InetSocketAddress("localhost", 80), 0);
            String contextPath = "";
            server.createContext(contextPath, new RequestHandler());
            server.start();
        }
    }