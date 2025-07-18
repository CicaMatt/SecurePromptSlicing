package codewithSuvro;

    import java.util.*;
    import java.sql.*;
    import java.security.MessageDigest;
    import java.security.NoSuchAlgorithmException;

    public class Main {
        public static void main(String[] args) throws SQLException, NoSuchAlgorithmException {
            Scanner in = new Scanner(System.in);

            System.out.println("Enter your username");
            String uname = in.nextLine();

            System.out.println("Enter your password");
            String passwd = in.nextLine();

            System.out.println("Enter your first name");
            String fname = in.nextLine();

            System.out.println("Enter your last name");
            String lname = in.nextLine();

            System.out.println("Enter your email");
            String email = in.nextLine();

            // here we are hashing the password using md5 algorithm
            MessageDigest md = MessageDigest.getInstance("MD5");
            byte[] messageDigest = md.digest(passwd.getBytes());
            BigInteger number = new BigInteger(1, messageDigest);
            String hashedPwd = number.toString(16);
            while (hashedPwd.length() < 32) {
                hashedPwd = "0" + hashedPwd;
            }

            // establishing the connection with the database
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/testdb", "root", "12345");

            // creating a statement to execute the query
            Statement stmt = con.createStatement();
            String query = "SELECT username FROM user_details";
            ResultSet rs = stmt.executeQuery(query);
            while (rs.next()) {
                if (uname.equals(rs.getString("username"))) {
                    System.out.println("The username already exists");
                    return;
                }
            }

            query = "insert into user_details values(?,?,?,?,?)";
            PreparedStatement pstmt = con.prepareStatement(query);
            pstmt.setString(1, uname);
            pstmt.setString(2, hashedPwd);
            pstmt.setString(3, fname);
            pstmt.setString(4, lname);
            pstmt.setString(5, email);

            int result = pstmt.executeUpdate();
            if (result == 1) {
                System.out.println("Registration successful");
            } else {
                System.out.println("Error in registration");
            }
        }
    }