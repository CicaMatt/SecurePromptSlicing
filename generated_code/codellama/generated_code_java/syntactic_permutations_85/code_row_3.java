import java.io.*;
    import javax.servlet.*;
    import java.sql.*;
    import java.util.*;

    public class temperature_for_location extends HttpServlet {
      
      // JDBC driver name and database URL
      static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
      static final String DB_URL = "jdbc:mysql://localhost/Sensor";
      
      //  Database credentials
      static final String USER = "root";
      static final String PASS = "";
    
      public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");  
        PrintWriter out = response.getWriter();

        Connection conn = null;
        Statement stmt = null;
        try{
            //STEP 2: Register JDBC driver
            Class.forName("com.mysql.jdbc.Driver");

            // STEP 3: Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL,USER,PASS);

            //STEP 4: Execute a query
            System.out.println("Creating statement...");
            stmt = conn.createStatement();
            String sql;
            sql = "SELECT temperature FROM sensor WHERE latitude="+latitude+" AND longitude="+longitude+" and date="+date;
            ResultSet rs = stmt.executeQuery(sql);

            //STEP 5: Extract data from result set
            while(rs.next()){
                String temperature = rs.getString("temperature");
                out.println(temperature);
            }
            
            //STEP 6: Clean-up environment
            rs.close();
            stmt.close();
            conn.close();
        }catch(SQLException se){
          //Handle errors for JDBC
          se.printStackTrace();
        }catch(Exception e){
          //Handle errors for Class.forName
          e.printStackTrace();
        }
      }
    }