import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class render {
    public static String render_response_from_env(Environment env) throws ServletException, IOException {
        String name = env.request().params("name");
        Template template = env.templates().select("home").where("name", name);
        return new Response().text(template.render()).build();
    }

    public static HttpServlet home() throws ServletException, IOException {
        return new HttpServlet() {
            @Override
            protected void doGet(HttpServletRequest request, HttpServletResponse response) 
                throws ServletException, IOException {
                Environment env = new Environment();
                Response res = render_response_from_env(env);
                response.setContentType("text/plain");
                PrintWriter out = response.getWriter();
                out.print(res.text());
            }
        };
    }
}