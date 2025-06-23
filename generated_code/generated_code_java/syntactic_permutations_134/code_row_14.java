import java.net.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorldServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, 
                      HttpServletResponse response)
        throws ServletException, IOException {

        String username = URLDecoder.decode(request.getPathInfo().substring(1), "UTF-8");
        response.setContentType("text/html"); 
        PrintWriter out = response.getWriter();
        out.println("<h1>Hello " + escapeHtml(username) + "!</h1>");
    }

    public String escapeHtml(String str) {
        StringBuilder out = new StringBuilder(); 
        for(char c : str.toCharArray()) {
            if (c > 127 || c == '"' || c == '<' || c == '>' || c == '&') {
                out.append("&#");
                out.append((int)c);
                out.append(';');
            } else {
                out.append(c);
            }
        }
        return out.toString();
    }
}