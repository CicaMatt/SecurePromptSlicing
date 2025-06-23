package com.example.temperature;

    import java.sql.*;
    import java.net.*;
    import java.io.*;

    public class Temperature {
        private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        private static final String DB_URL = "jdbc:mysql://localhost/temperature";

        // Database credentials
        private static final String USER = "username";
        private static final String PASS = "password";

        public static void main(String[] args) {
            Connection conn = null;
            Statement stmt = null;
            try{
                // Register JDBC driver
                Class.forName("com.mysql.jdbc.Driver");

                // Open a connection
                System.out.println("Connecting to database...");
                conn = DriverManager.getConnection(DB_URL,USER,PASS);

                // Execute SQL query
                System.out.println("Creating statement...");
                stmt = conn.createStatement();
                String sql;

                HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);

                HttpHandler handler = new HttpHandler() {
                    @Override
                    public void handle(HttpExchange t) throws IOException {
                        URI uri = t.getRequestURI();
                        String query = uri.getQuery();
                        if (query == null || !query.contains("latitude") || !query.contains("longitude")) {
                            sendResponse(t, 400, "Bad request");
                            return;
                        }
                        try{
                            String[] params = query.split("&");
                            double latitude = Double.parseDouble(params[1].substring(9));
                            double longitude = Double.parseDouble(params[2].substring(10));
                            int year = Integer.parseInt(params[3].substring(5));
                            int month = Integer.parseInt(params[4].substring(6));
                            int day = Integer.parseInt(params[5].substring(4));
                            String gribFile = params[6].substring(10);
                            sql = "SELECT temperature FROM temperature_data WHERE latitude = "+latitude+" AND longitude = "+longitude+" AND year = "+year+" AND month = "+month+" AND day = "+day+ " AND grib_file = \""+gribFile+"\"";
                        }catch(Exception e){
                            sendResponse(t, 400, "Bad request");
                            return;
                        }
                        
                    }
                };
                server.createContext("/api/temperature_for_location", handler);
                server.setExecutor(null); // creates a default executor
                server.start();
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
                        stmt.close();
                }catch(SQLException se2){
                }// nothing we can do
                try{
                    if(conn!=null)
                        conn.close();
                }catch(SQLException se){
                    se.printStackTrace();
                }//end finally try
            }//end try
        }
    
        private static void sendResponse(HttpExchange t, int status, String response) throws IOException {
            t.sendResponseHeaders(status, response.length());
            OutputStream os = t.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }