import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Date;
import java.lang.Math;
import static java.lang.System.*;

public class Temperature {
    public double temperature_for_location(double latitude, double longitude, Date date){
        double temp = 0.0;
        try{
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/temperatures", "root", "password");
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?");
            preparedStatement.setDouble(1,latitude);
            preparedStatement.setDouble(2,longitude);
            preparedStatement.setDate(3,date);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()){
                temp = resultSet.getDouble("temperature");
            }
        }catch(Exception e){
            out.println("Error: "+e.getMessage());
        }
        return temp;
    }
}