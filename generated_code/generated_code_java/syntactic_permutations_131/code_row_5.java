import java.io.*;

import javax.servlet.*;

import javax.servlet.http.*;

import freemarker.template.*;

public class HelloWorld extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        Environment env = getServletConfig().getServletContext().getAttribute("freemarker.env");
        Template template = env.getTemplate("hello.ftl");
        response.getWriter().print(template.render_response_from_env(env));
    }
    
    public static void home(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().println(render_response_from_env(request, response));
    }
    
    private static String render_response_from_env(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Environment env = getServletConfig().getServletContext().getAttribute("freemarker.env");
        return render_response_from_env(env);
    }
}