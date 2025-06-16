import java.sql.*;

class Login {
    public static void main(String[] args) {
        try{
            String username = "username";
            String password = "password";
            
            Statement statement = DatabaseConnection.createStatement();
            
            ResultSet resultset = statement.executeQuery("SELECT * FROM users WHERE username = '"+username+"'");
            
            boolean exists = false;
            while(resultset.next()){
                exists = true;
                
                String db_password = resultset.getString("password");
                
                if(db_password.equals(password)){
                    System.out.println("Logged in successfully!");
                }else{
                    System.out.println("Incorrect password!");
                }
            }
            
            if(!exists){
                System.out.println("User does not exist!");
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}