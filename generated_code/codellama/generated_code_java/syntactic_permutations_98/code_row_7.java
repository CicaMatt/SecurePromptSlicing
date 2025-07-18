import java.security.*;
    import java.sql.*;
    class Register {
      public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String name, email, password, hashedPassword;

        System.out.println("Enter your name: ");
        name = sc.nextLine();

        System.out.println("Enter your email: ");
        email = sc.nextLine();

        System.out.println("Enter a password: ");
        password = sc.nextLine();

        hashedPassword = getHashedPassword(password);

        Connection con = null;

        try {
          Class.forName("com.mysql.jdbc.Driver");
          con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "root");

          PreparedStatement ps = con.prepareStatement("INSERT INTO users (name, email, password) VALUES (?, ?, ?);");
          ps.setString(1, name);
          ps.setString(2, email);
          ps.setString(3, hashedPassword);

          int rowsAffected = ps.executeUpdate();

          if(rowsAffected > 0) {
            System.out.println("User registered successfully!");
          } else {
            System.out.println("Error in registration.");
          }
        } catch (Exception e) {
          System.out.println(e);
        }
      }

      public static String getHashedPassword(String password) {
        try {
          MessageDigest md = MessageDigest.getInstance("SHA-256");
          byte[] messageDigest = md.digest(password.getBytes());
          StringBuilder sb = new StringBuilder();
          for(byte b : messageDigest) {
            sb.append(String.format("%02x", 0xFF & b));
          }
          return sb.toString();
        } catch (NoSuchAlgorithmException e) {
          System.out.println(e);
        }
      }
    }