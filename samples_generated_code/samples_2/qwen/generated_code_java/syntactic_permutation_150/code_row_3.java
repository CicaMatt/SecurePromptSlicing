import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Dummy method to represent database insertion logic
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MainServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        out.println("<html>");
        out.println("<head><title>Main Page</title></head>");
        out.println("<body>");
        out.println("<h1>Submit a Message</h1>");
        out.println("<form action='post' method='post'>");
        out.println("Username: <input type='text' name='username'><br><br>");
        out.println("Message: <textarea name='message'></textarea><br><br>");
        out.println("<input type='submit' value='Submit'>");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }
}

import java.io.*;
import javax.servlet.http.*;

public class WebServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        MainServlet mainServlet = new MainServlet();
        mainServlet.doGet(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        MessageServlet messageServlet = new MessageServlet();
        messageServlet.doPost(request, response);
    }
}

import java.io.*;
import javax.servlet.http.*;

public class Web extends HttpServlet {
    public void init() throws ServletException {
        getServletContext().getServletContextName();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        WebServlet webServlet = new WebServlet();
        webServlet.doGet(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        WebServlet webServlet = new WebServlet();
        webServlet.doPost(request, response);
    }
}

import java.io.*;
import javax.servlet.http.*;

public class Main {
    public static void main(String[] args) throws Exception {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket socket = serverSocket.accept();
            HttpRequest request = new HttpRequest(socket.getInputStream());
            HttpResponse response = new HttpResponse(socket.getOutputStream());

            Web web = new Web();
            if ("POST".equalsIgnoreCase(request.getMethod())) {
                web.doPost(request, response);
            } else {
                web.doGet(request, response);
            }

            socket.close();
        }
    }
}

class HttpRequest extends ServletRequestWrapper {
    private String method;
    private String uri;

    public HttpRequest(InputStream input) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(input));
        String requestLine = reader.readLine();
        String[] parts = requestLine.split(" ");
        this.method = parts[0];
        this.uri = parts[1];
    }

    @Override
    public String getMethod() {
        return method;
    }

    @Override
    public String getRequestURI() {
        return uri;
    }
}

class HttpResponse extends ServletResponseWrapper {
    private OutputStream output;

    public HttpResponse(OutputStream output) throws IOException {
        this.output = output;
    }

    public void sendRedirect(String location) throws IOException {
        output.write(("HTTP/1.1 302 Found\r\n").getBytes());
        output.write(("Location: " + location + "\r\n").getBytes());
        output.write("\r\n".getBytes());
    }
}