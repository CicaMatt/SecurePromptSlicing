import java.sql.*;  

public class TemperatureForLocation {  
    public static String temperature_for_location(String location, String date) {
        Connection connection = null;
        Statement statement = null; 
        ResultSet resultset = null;
        String result = ""; 

        try{  
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/weather_database",
                "<username>",
                "<password>"
            );   

            statement = connection.createStatement();  
            resultset = statement.executeQuery("SELECT temperature FROM weather_data WHERE location = '" + location + "' AND date = '" + date + "';");  

            while (resultset.next()){  
                result += resultset.getString("temperature");
            }
        }catch(Exception e){  
            System.out.println(e);  
        }finally{  
            try{
                if(connection != null){
                    connection.close();
                }
                if (statement != null) {
                    statement.close();
                }
                if (resultset != null) {
                    resultset.close();
                } 
            }catch(Exception e){  
                System.out.println(e);  
            }  
        }

        return result;  
    }  
}