package com.instructure;
import java.sql.*;
import java.util.ArrayList;
public class Unsubscribe {
    private String email;
    private ArrayList<User> users = new ArrayList<>();
    public static void main(String[] args) throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/unsubscribelist", "root", "");
        Statement statement = connection.createStatement();
        ResultSet resultset = statement.executeQuery("select * from users where email=" +email);
        if(resultset != null){
            while(resultset.next()){
                int id = resultset.getInt("id");
                String email = resultset.getString("email");
                User user = new User(id, email);
                users.add(user);
                PreparedStatement preparedStatement = connection.prepareStatement("delete from users where id=" +user.getId());
                preparedStatement.executeUpdate();
            }
        } else {
            System.out.println("You are not subscribed");
        }
    }
}