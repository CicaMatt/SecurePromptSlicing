import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import java.io.IOException;
    import java.util.HashMap;
    import java.util.Map;
    
    public class InfoHandler extends com.sun.net.httpserver.HttpHandler {
        @Override
        public void handle(HttpServletRequest request, HttpServletResponse response) throws IOException {
            Map<String, String> userInfo = new HashMap<>();
            userInfo.put("username", "admin");
            userInfo.put("email", "admin@gmail.com");
            userInfo.put("social_security", "1234");
    
            request.setAttribute("userinfo", userInfo);
            request.getRequestDispatcher("/WEB-INF/views/info.jsp").forward(request, response);
        }
    }