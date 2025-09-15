import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            response.sendRedirect("home.html");
        } else {
            response.sendRedirect("login.html");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }
}

import java.io.*;

public class LoginHTMLGenerator extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login</h2>");
        out.println("<form method='post' action='login'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}

import java.io.*;

public class HomeHTMLGenerator extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome to the Home Page</h2>");
        out.println("</body></html>");
    }
}

import java.io.*;

public class WebServer extends HttpServlet {
    public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket client = server.accept();
            new Thread(new ClientHandler(client)).start();
        }
    }

    static class ClientHandler implements Runnable {
        private Socket socket;

        public ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                 PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {

                String requestLine = in.readLine();
                if (requestLine != null && requestLine.startsWith("POST /login")) {
                    StringBuilder requestBody = new StringBuilder();
                    String line;
                    while (!(line = in.readLine()).isBlank()) ;
                    while ((line = in.readLine()) != null) {
                        requestBody.append(line);
                    }
                    String[] params = requestBody.toString().split("&");
                    String username = "";
                    String password = "";
                    for (String param : params) {
                        if (param.startsWith("username=")) {
                            username = param.substring(9);
                        } else if (param.startsWith("password=")) {
                            password = param.substring(9);
                        }
                    }

                    if ("admin".equals(username) && "password123".equals(password)) {
                        out.println("HTTP/1.1 302 Found");
                        out.println("Location: /home.html");
                        out.println();
                    } else {
                        out.println("HTTP/1.1 302 Found");
                        out.println("Location: /login.html");
                        out.println();
                    }
                } else if (requestLine != null && requestLine.startsWith("GET /login.html")) {
                    sendFile(out, "login.html");
                } else if (requestLine != null && requestLine.startsWith("GET /home.html")) {
                    sendFile(out, "home.html");
                } else {
                    out.println("HTTP/1.1 404 Not Found");
                    out.println();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        private void sendFile(PrintWriter out, String fileName) throws IOException {
            File file = new File(fileName);
            if (!file.exists()) {
                out.println("HTTP/1.1 404 Not Found");
                out.println();
                return;
            }

            out.println("HTTP/1.1 200 OK");
            out.println("Content-Type: text/html");
            out.println();

            try (BufferedReader fileReader = new BufferedReader(new FileReader(file))) {
                String line;
                while ((line = fileReader.readLine()) != null) {
                    out.println(line);
                }
            }
        }
    }
}
