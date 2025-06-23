import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import org.apache.velocity.Template;
    import org.apache.velocity.VelocityContext;
    import org.apache.velocity.app.VelocityEngine;
    import org.eclipse.jetty.server.*;
    import org.eclipse.jetty.servlet.*;

    @WebServlet("/hello")
    public class HelloWorld extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String userName = request.getParameter("username");
            Template t = velocityEngine.getTemplate("hello.html");
            VelocityContext ctx = new VelocityContext();
            ctx.put("userName", userName);
            PrintWriter writer = response.getWriter();
            t.merge(ctx, writer);
        }
    }