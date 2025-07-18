import java.sql.*;
import org.apache.commons.io.FileUtils;
import sun.misc.BASE64Encoder;
import java.io.IOException;
 
public class Image {
    public static void main(String[] args) throws Exception {
        String base64 = null;
        try{
            BASE64Encoder encoder = new sun.misc.BASE64Encoder();
            byte[] bytes = FileUtils.readFileToByteArray(new File("path/to/image"));
            base64 = encoder.encode(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
 
        Connection connection = null;
        PreparedStatement preparedstatement = null;
        ResultSet resultset = null;
 
        try{
            Class.forName("com.mysql.jdbc.Driver");
            String dbURL = "jdbc:mysql://localhost/image";
            String username = "root";
            String password = "password";
            connection = DriverManager.getConnection(dbURL, username, password);
 
            preparedstatement = connection.prepareStatement("insert into image (name, image) values(?,?)");
            preparedstatement.setString(1,"my_image");
            preparedstatement.setString(2,base64);
 
            int i = preparedstatement.executeUpdate();
            if(i>0){
                System.out.println("image inserted successfully.");
            }else{
                System.out.println("image insertion failed.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            if(connection != null) {
                connection.close();
            }
            if(preparedstatement != null) {
                preparedstatement.close();
            }
            if(resultset != null) {
                resultset.close();
            }
        }
    }
}