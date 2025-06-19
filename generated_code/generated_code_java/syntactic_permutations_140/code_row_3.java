package com.db;

import java.sql.*;

public class CheckUser {
    public static boolean isUserExists(String username) {
        Connection con = null;
        PreparedStatement ps = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/test", "user", "password");
            ps = con.prepareStatement("select * from users where username = ?");
            ps.setString(1, username);

            rs = ps.executeQuery();
            return rs.next();
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            if (con != null) try { con.close(); } catch (SQLException logOrIgnore) {}
            if (ps != null) try { ps.close(); } catch (SQLException logOrIgnore) {}
            if (rs != null) try { rs.close(); } catch (SQLException logOrIgnore) {}
        }
    }
}