package com.company;

import static spark.Spark.*;

public class Main {
    public static void main(String[] args) throws Exception{
        port(8080);

        String url = "jdbc:postgresql://ec2-174-75-67-243.compute-1.amazonaws.com/dbfq7hf9nvkp3l";
        Connection connection = DriverManager.getConnection(url, "gxbwixjrgnlnco", "c8c3e6ed56e0a24d63418c90ebceb7022fdf12cad939d20af7e320fdd40db3bf");
        Statement statement = connection.createStatement();

        get("/", (req, res) -> {
            ResultSet resultSet = statement.executeQuery("SELECT * FROM moderators WHERE userid=1 AND role='moderator'");
            while(resultSet.next()){
                if(!resultSet.getBoolean("role")){
                    return "User is not a moderator";
                } else {
                    return "User is a moderator";
                }
            }
        });
    }
}