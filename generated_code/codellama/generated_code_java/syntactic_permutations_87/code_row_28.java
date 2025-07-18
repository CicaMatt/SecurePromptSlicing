import java.sql.*;
public String temperature_for_location(int latitude, int longitude, Date date){
    Connection conn = null;
    PreparedStatement stmt = null;
    ResultSet rs = null;
    try{
        String url = "jdbc:sqlite:temperature.db";
        conn = DriverManager.getConnection(url);

        String sql = "SELECT temperature FROM temperature WHERE latitude=? AND longitude=? AND date=?"
        stmt = conn.prepareStatement(sql);
        stmt.setInt(1,latitude);
        stmt.setInt(2,longitude);
        stmt.setDate(3,date);

        rs = stmt.executeQuery();

        while(rs.next()){
            return String.valueOf(rs.getDouble("temperature"));
        }
    }catch(SQLException e){
        System.out.println(e.getMessage());
    }finally{
        try{
            if(stmt!=null){
                stmt.close();
            }
        }catch(SQLException se2){
            System.out.println(se2.getMessage());
        }try{
            if(conn!=null){
                conn.close();
            }
        }catch(SQLException se3){
            System.out.println(se3.getMessage());
        }
    return null;
}