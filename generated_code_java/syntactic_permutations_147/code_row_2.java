package com.app.controller;

    import java.util.*;
    import javax.sql.*;
    import java.sql.*;
    import org.springframework.web.bind.annotation.*;
    import org.springframework.stereotype.*;

    @Controller
    public class BuyOrder {
        @RequestMapping(value="/buy_order", method=RequestMethod.POST)
        public String buyOrder(@ModelAttribute("stock") Stock stock){
            Connection conn = null;
            Statement stmt = null;
            try{
                Class.forName("com.mysql.cj.jdbc.Driver");
                conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");

                String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
                stmt = conn.prepareStatement(sql);
                stmt.setString(1, stock.getName());
                stmt.setInt(2, stock.getQuantity());

                int result = stmt.executeUpdate();
            }catch(Exception e){
                System.out.println(e);
            }

            return "redirect:/stock_view";
        }
    }

    package com.app.entity;

    public class Stock {
        private int id;
        private String name;
        private int quantity;

        public Stock(){}

        public Stock(String name, int quantity){
            this.name = name;
            this.quantity = quantity;
        }

        public int getId(){
            return id;
        }

        public String getName(){
            return name;
        }

        public void setName(String name){
            this.name = name;
        }

        public int getQuantity(){
            return quantity;
        }

        public void setQuantity(int quantity){
            this.quantity = quantity;
        }
    }

    package com.app.entity;

    import org.springframework.data.repository.CrudRepository;

    public interface StockRepository extends CrudRepository<Stock, Integer>{

    }