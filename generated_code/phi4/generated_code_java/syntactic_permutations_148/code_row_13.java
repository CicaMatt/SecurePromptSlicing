import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect(request.getContextPath() + "/main");
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to insert message.");
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        // Mock implementation of database insertion logic
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        return true; // Assume the operation is successful
    }
}

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/main")
public class MainServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        try {
            String messagesHTML = getMessageDisplayHtml();
            out.println("<html><head><title>Main Page</title></head><body>");
            out.println(messagesHTML);
            out.println("</body></html>");
        } finally {
            out.close();
        }
    }

    private String getMessageDisplayHtml() {
        // Mock implementation of fetching messages from a database
        StringBuilder htmlBuilder = new StringBuilder("<h1>Messages</h1><ul>");
        
        // Example data to simulate fetched records
        String[][] messagesData = {
                {"Alice", "Hello World!"},
                {"Bob", "Hi there!"}
        };

        for (String[] message : messagesData) {
            htmlBuilder.append("<li>").append(message[0]).append(": ").append(message[1]).append("</li>");
        }

        htmlBuilder.append("</ul>");
        return htmlBuilder.toString();
    }
}

import org.apache.catalina.startup.Tomcat;

public class WebAppLauncher {

    public static void main(String[] args) throws Exception {
        Tomcat tomcat = new Tomcat();

        tomcat.setPort(8080);
        String webappDirLocation = System.getProperty("java.io.tmpdir") + "/webapps/webapp";

        Context ctx = tomcat.addWebapp("/", webappDirLocation);

        ClassLoader cloader = WebAppLauncher.class.getClassLoader();
        String docBase = "C:/path/to/your/webapp";
        ctx.setResources(cloader);
        
        tomcat.start();
        tomcat.getServer().await();
    }
}
