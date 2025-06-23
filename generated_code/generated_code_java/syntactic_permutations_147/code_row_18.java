package com.jwt.starter;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Stock {

    @PostMapping("/buy_order")
    public String buyOrder(HttpServletRequest request) throws SQLException, ClassNotFoundException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        // Database connectivity using MySQL
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/stock_management", "root", "password");

        // Prepared statement for inserting data into the database
        String insertSQL = "INSERT INTO stock (stockName, quantity) VALUES (?, ?)";
        PreparedStatement stmt = con.prepareStatement(insertSQL);

        // Set values in prepared statements
        stmt.setString(1, stockName);
        stmt.setInt(2, quantity);

        int rowsAffected = stmt.executeUpdate();

        if (rowsAffected > 0) {
            return "Data inserted into the database.";
        } else {
            return "Data not inserted into the database.";
        }
    }
}