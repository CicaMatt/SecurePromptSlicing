import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, stockName);
            statement.setInt(2, quantity);

            statement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }

        response.sendRedirect("stock_view");
    }
}

public class ServerApp {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Listening on port 8080...");

            while (true) {
                Socket clientSocket = serverSocket.accept();
                ClientHandler clientThread = new ClientHandler(clientSocket);
                new Thread(clientThread).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static class ClientHandler implements Runnable {

        private final Socket clientSocket;

        public ClientHandler(Socket socket) {
            this.clientSocket = socket;
        }

        @Override
        public void run() {
            try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                 PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)) {

                StringBuilder formHTML = new StringBuilder();
                formHTML.append("<html><body>");
                formHTML.append("<form action='http://localhost:8080/buy_order' method='POST'>");
                formHTML.append("Stock Name: <input type='text' name='stock_name'><br>");
                formHTML.append("Quantity: <input type='number' name='quantity'><br>");
                formHTML.append("<input type='submit' value='Submit Order'>");
                formHTML.append("</form></body></html>");

                out.println(formHTML.toString());

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}


**Note**: Before running this code, ensure you have a MySQL database named `your_database` with a table called `orders` and columns `stock_name` of type VARCHAR and `quantity` of type INT. Also, replace `"username"` and `"password"` with your actual database credentials. This example uses a very basic form of handling HTTP requests for demonstration purposes and does not include error handling or security measures such as input validation/sanitization or HTTPS that are necessary for production applications.