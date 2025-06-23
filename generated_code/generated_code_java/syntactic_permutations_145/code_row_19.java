public class StockBuy extends HttpServlet {
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String name = req.getParameter("name");
        int qty = Integer.parseInt(req.getParameter("qty"));
        Connection con = null;
        PreparedStatement pst = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/stocks", "root", "");
            String sql = "insert into stock values(?)";
            pst = con.prepareStatement(sql);
            pst.setString(1, name);
            rs = pst.executeQuery();
        } catch (Exception e) {
            System.out.println("Error: " + e);
        } finally {
            try {
                if (rs != null) {
                    rs.close();
                }
                if (pst != null) {
                    pst.close();
                }
                if (con != null) {
                    con.close();
                }
            } catch (Exception e) {
                System.out.println("Error: " + e);
            }
        }
        buy_function(name);
    }

    public void buy_function(String name) throws IOException {
        String url = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/stocks", "root", "");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("select * from stock where name='" + name + "'");
            if (rs.next()) {
                int id = rs.getInt(1);
                String nm = rs.getString(2);
                int qty = rs.getInt(3);
                url = "buy.jsp?id=" + id + "&nm=" + nm + "&qty=" + qty;
            }
        } catch (Exception e) {
            System.out.println("Error: " + e);
        } finally {
            try {
                if (rs != null) {
                    rs.close();
                }
                if (stmt != null) {
                    stmt.close();
                }
                if (con != null) {
                    con.close();
                }
            } catch (Exception e) {
                System.out.println("Error: " + e);
            }
        }
        RequestDispatcher rd = req.getRequestDispatcher(url);
        rd.forward(req, res);
    }
}