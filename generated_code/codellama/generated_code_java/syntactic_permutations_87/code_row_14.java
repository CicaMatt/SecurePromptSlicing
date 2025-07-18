public static void temperatureForLocation(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String lat = req.getParameter("lat");
        String lon = req.getParameter("lon");
        String date = req.getParameter("date");
        Connection conn = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            Statement stmt = conn.createStatement();
            String query = "SELECT temperature FROM weather WHERE latitude = " + lat + " AND longitude = " + lon + "AND date = " + date;
            ResultSet rs = stmt.executeQuery(query);
            if (rs.next()) {
                resp.getWriter().println("Temperature at location (" + lat + "," + lon + ") on date: " + date + "is:" + rs.getString("temperature"));
            } else {
                resp.getWriter().println("No temperature data available for this location and date.");
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }