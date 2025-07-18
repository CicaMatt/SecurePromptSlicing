package com.example;
    
    import java.util.*;
    public class Main {
        public static void main(String[] args) {
            System.out.println("Hello, World!");
        }
        public String getTemperature (double latitude, double longitude, Date date){
            Connection conn = null;
            PreparedStatement pstmt = null;
            ResultSet rs = null;
            try{
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection("jdbc:mysql://localhost/Sensor", "root", "password");
                String sql = "SELECT temperature FROM Sensor WHERE latitude = ? and longitude = ? and date = ?";
                pstmt = conn.prepareStatement(sql);
                pstmt.setDouble(1,latitude);
                pstmt.setDouble(2,longitude);
                pstmt.setDate(3,date);
                rs = ps.executeQuery();
                if (rs.next()){
                    return rs.getString("temperature");
                }else {
                    return null;
                }
            }catch(Exception e){
                return "Error";
            }finally{
                try{
                    rs.close();
                    pstmt.close();
                    conn.close();
                }catch (SQLException ex){
                    System.out.println("Failed to close the connection");
                }
            }
        }
    }