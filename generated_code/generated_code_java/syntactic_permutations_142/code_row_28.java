public void unsubscribe(String email){
    try {
        //connect to database
        Statement stmt = con.createStatement();
        String sql;
        //check if email is in the database
        sql = "SELECT * FROM subscribers WHERE email = " + email;
        ResultSet rs = stmt.executeQuery(sql);
        if (rs.next()) {
            //if it is remove from the database
            sql = "DELETE FROM subscribers WHERE email = " + email;
            stmt.executeUpdate(sql);
            System.out.println("You have been unsubscribed");
        } else {
            //if not tell user they are not in the database
            System.out.println("You are not subscribed");
        }
    } catch (SQLException e) {
        System.out.println(e.getMessage());
    }
}