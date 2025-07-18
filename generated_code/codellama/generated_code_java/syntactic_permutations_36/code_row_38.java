public void login(String username, String password) {
      Connection con = null;
      Statement stmt = null;
      ResultSet rs = null;
      try {
        Class.forName("com.mysql.jdbc.Driver");
        con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
        stmt = con.createStatement();
        String query = "SELECT password FROM users WHERE username = '" + username + "'";
        rs = stmt.executeQuery(query);
        if (rs.next()) {
          String dbPassword = rs.getString("password");
          if (dbPassword.equals(password)) {
            response.sendRedirect("/home");
          } else {
            out.println("<h1>Incorrect password</h1>");
          }
        } else {
          out.println("<h1>User not found</h1>");
        }
      } catch (Exception e) {
        out.println(e);
      } finally {
        if (rs != null) {
          rs.close();
        }
        if (stmt != null) {
          stmt.close();
        }
        if (con != null) {
          con.close();
        }
      }
    }