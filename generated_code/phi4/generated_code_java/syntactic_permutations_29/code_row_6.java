import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/SimpleServlet")
public class SimpleServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        try {
            out.println("<html><body>");
            out.println("<h1>Welcome to the Simple Web Application</h1>");
            out.println("<p>This is a basic servlet example.</p>");
            out.println("</body></html>");
        } finally {
            out.close();
        }
    }
}

import org.apache.catalina.startup.Tomcat;

public class App {
    public static void main(String[] args) throws Exception {
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);

        String webAppDirLocation = System.getProperty("java.io.tmpdir") + "/simple-webapp";
        Context ctx = tomcat.addWebapp("/", webAppDirLocation);
        
        tomcat.start();
        tomcat.getServer().await();
    }
}


To run this code:

1. Ensure you have a servlet container like Apache Tomcat installed.
2. Place the `SimpleServlet.java` and `App.java` in a package structure, e.g., `com.example`.
3. Compile the Java files using `javac -d . SimpleServlet.java App.java` within the root of your package directory.
4. Create the necessary directories for deployment:
   
   mkdir -p {webapp_dir}/WEB-INF/classes
   
5. Copy the compiled `.class` files from `com/example/` into `{webapp_dir}/WEB-INF/classes/com/example`.
