import java.util.*;
import java.io.*;
import java.sql.*;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import org.apache.tomcat.jdbc.pool.DataSource;
import org.apache.tomcat.jdbc.pool.PoolProperties;
import javax.servlet.http.*;
import javax.servlet.annotation.WebServlet;

@WebServlet(urlPatterns = {"/register"})
public class Register extends HttpServlet {
    private DataSource dataSource;
    public void init() throws ServletException {
        PoolProperties p = new PoolProperties();
        p.setUrl("jdbc:mysql://localhost:3306/accounts");
        p.setDriverClassName("com.mysql.cj.jdbc.Driver");
        p.setUsername("root");
        p.setPassword("password");
        dataSource = new DataSource();
        dataSource.setPoolProperties(p);
    }
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Connection conn = null;
        PreparedStatement ps = null;
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        try {
            conn = dataSource.getConnection();
            Mac mac = Mac.getInstance("HmacSHA256");
            SecretKeySpec secret_key = new SecretKeySpec("mysecret".getBytes(), "HmacSHA256");
            mac.init(secret_key);
            String hashedPassword = bytesToHex(mac.doFinal(password.getBytes()));
            ps = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
            ps.setString(1, username);
            ps.setString(2, hashedPassword);
            int count = ps.executeUpdate();
            response.sendRedirect("/login.html");
        } catch (SQLException e) {
            throw new ServletException("SQL error", e);
        } finally {
            if (ps != null) try { ps.close(); } catch (SQLException logOrIgnore) {}
            if (conn != null) try { conn.close(); } catch (SQLException logOrIgnore) {}
        }
    }
    
    public static String bytesToHex(byte[] hash) {
        StringBuilder sb = new StringBuilder(hash.length * 2);
        for (int i = 0; i < hash.length; i++) {
            if ((0xff & hash[i]) < 0x10) {
                sb.append("0");
            }
            sb.append(Integer.toHexString(0xff & hash[i]));
        }
        return sb.toString();
    }
}