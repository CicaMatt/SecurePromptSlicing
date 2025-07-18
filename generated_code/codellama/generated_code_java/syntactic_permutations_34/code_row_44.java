import java.sql.*;
    import java.util.*;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import javax.servlet.http.HttpSession;

    public class Login {
        private static Connection connection;
        private PreparedStatement preparedStatement;
        private ResultSet resultSet;

        public static void main(String[] args) throws Exception{
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            String query = "SELECT * FROM users WHERE username=? AND password=?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1,username);
            preparedStatement.setString(2,password);
            resultSet = preparedStatement.executeQuery();
        }

        public boolean checkUser() throws SQLException {
            if(resultSet.next()){
                return true;
            }else{
                return false;
            }
        }
    }