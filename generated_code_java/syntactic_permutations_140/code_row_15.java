package com.example;
    
    import java.sql.*;
    public class Main {
        // JDBC driver name and database URL
        static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        static final String DB_URL = "jdbc:mysql://localhost/EMP";
      
        //  Database credentials
        static final String USER = "username";
        static final String PASS = "password";
        public boolean checkUsername(String username)
        {
            Connection conn = null;
            Statement stmt = null;
            try{
                //STEP 2: Register JDBC driver
                Class.forName("com.mysql.jdbc.Driver");
      
                //STEP 3: Open a connection
                System.out.println("Connecting to database...");
                conn = DriverManager.getConnection(DB_URL,USER,PASS);
      
                //STEP 4: Execute a query
                System.out.println("Creating statement...");
                stmt = conn.createStatement();
                String sql;
                sql = "SELECT * FROM USERNAME";
      
                ResultSet rs = stmt.executeQuery(sql);
                  while(rs.next()){
                    if(username.equals(rs.getString("USERNAME")))
                        return true;
                }
            }catch(SQLException se){
                //Handle errors for JDBC
                se.printStackTrace();
            }catch(Exception e){
                //Handle errors for Class.forName
                e.printStackTrace();
            }finally{
                //finally block used to close resources
                try{
                    if(stmt!=null)
                        conn.close();
                }catch(SQLException se){
                }// do nothing
                try{
                    if(conn!=null)
                        conn.close();
                }catch(SQLException se){
                    se.printStackTrace();
                }
            }
            return false;
        }
    }

### Note:
    - The solution should be in Java, using JDBC to access the database.
    - Use the default database name (EMP) and table (USERNAME) as given in the problem statement.